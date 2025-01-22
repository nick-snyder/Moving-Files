//
// simple test for the concurrent buffer
//
// create two threads which communicate through the buffer
//
// the main thread opens a file (name given on commandline) and
// passes the FILE* to the first thread through the parameter to
// the first thread's work function
//
// the first thread reads lines from the file, passing each line via
// the buffer to the second thread.
//
// the second thread sums the number of characters in the lines
//
// at EOF the first thread sends a NULL pointer to the buffer and
// terminates
//
// when the second thread receives the NULL pointer it returns the
// sum through the void* return value of its work function
//
// the main thread uses thread join to wait for the two threads to
// finish (the join also cleans up the memory for the threads)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "concurrentBuffer.h"

#define DEBUG 0

// allow this to be overridden at compile time
// e.g. gcc -DBUFFER_SIZE=1 ...
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

#define MAX_LINE_LENGTH 1024

#define MAX_T 12

pthread_t pt[MAX_T];

// mutex to protect update to global histogram
pthread_mutex_t mu;

// global histogram
// maximum index is [50] for words of length 50
int histogram[51];  

// the work functions for the threads
static void *work1(void *);
static void *work2(void *);

typedef struct Stack
{
    int size;
    int capacity;
    int array[MAX_LINE_LENGTH];
}
Stack;

// struct to be used to pass information to the first thread
typedef struct INFO
{
    // FILE *fp;
    char *filename;
    void *buffer;
} 
INFO;

int main(int argc, char *argv[])
{
    // make sure there is at least one input file
    if (argc < 2)
    {
        fprintf(stderr, "Usage: countChars file\n");
        exit(-1);
    }

    // initialize mutex to protect global histogram
    if (pthread_mutex_init(&mu, NULL) != 0)
    {
        exit(-1);
    }

    // for every input file
    for (int i = 1; i < argc; i++)
    {
        // allocate a struct
        INFO *ip = malloc(sizeof(INFO));

        // create the concurrent buffer
        void *cBuffer = createConcurrentBuffer(BUFFER_SIZE);
        if (cBuffer == NULL)
        {
            fprintf(stderr, "can't create the concurrent buffer\n");
            exit(-1);
        }

        // set the filename member to the argument on the command line
        ip->filename = argv[i]; 

        #if DEBUG
            printf("filename: %s\n", ip->filename);
        #endif

        // set the buffer member to the concurrent buffer
        ip->buffer = cBuffer;

        // create the producer thread with that struct and send it to work
        if (pthread_create(&pt[i], NULL, work1, ip) != 0)
        {
            fprintf(stderr, "can't create thread 1\n");
            exit(-1);
        }

        // create the consumer thread with the buffer and send it to work
        if (pthread_create(&pt[i], NULL, work2, cBuffer) != 0)
        {
            fprintf(stderr, "can't create thread 2\n");
            exit(-1);
        }

        free(ip);
        // deleteConcurrentBuffer(cBuffer);     // already freed in work2()
    }

    // pthread_mutex_destroy(&mu);

    // wait for the producer threads to finish
    for (int i = 1; i < argc; i+=2)
    {
        if (pthread_join(pt[i], NULL))
        {
            fprintf(stderr, "join for producer thread fails\n");
            exit(-1);
        }
    }

    // wait for the consumer threads to finish
    for (int i = 2; i < argc; i+=2)
    {
        // void *ret;
        if (pthread_join(pt[i], NULL))
        {
            fprintf(stderr, "join for thread 2 fails\n");
            exit(-1);
        }
    }

    // print full histogram
    for (int i = 6; i < 51; i++)
    {
        printf("%d %d\n", i, histogram[i]);
    }
}

// get a line from an opened file
//   returns NULL at EOF
//   assumes a line is less than MAX_LINE_LENGTH characters long
//   mallocs space for the return value
//   line returned includes the newline on the end
//   last line might not include newline if last line is terminated by EOF
//   in this case one more call to readLine is required for NULL to be returned

static char *getLine(FILE *fp)
{
    char buf[MAX_LINE_LENGTH];
    int i = 0;
    int c = getc(fp);
    
    if (c == EOF)
    {
        // close the file
        fclose(fp);
        return NULL;
    } 

    while (c != EOF && c != '\n')
    {
        buf[i] = c;
        i += 1;
        if (i == MAX_LINE_LENGTH)
        {
            fprintf(stderr, "maximum line length (%d) exceeded\n", MAX_LINE_LENGTH);
            exit(-1);
        }
        c = getc(fp);
    }
    if (c == '\n')
    {
        buf[i] = c;
        i += 1;
    }
    buf[i] = 0;
    char *s = malloc(i+1);
    if (s == NULL)
    {
        fprintf(stderr, "malloc failed in getLine\n");
        exit(-1);
    }
    strcpy(s, buf);
    return s;
}

// work function for the first thread (the producer)
static void *work1(void *info)
{
    INFO *ip = info;

    // open the file to be read
    FILE *fp = fopen(ip->filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "can't open %s\n", ip->filename);
        exit(-1);
    }

    // read the lines in the file
    char *line;
    while ((line = getLine(fp)) != NULL)
    {
        // put each line in the buffer as a block
        putConcurrentBuffer(ip->buffer, line);
    }

    // put a NULL to indicate EOF
    putConcurrentBuffer(ip->buffer, NULL);

    fclose(fp);     // causes invalid frees

    return NULL;
}

// work function for the second thread (the consumer)
static void *work2(void *buffer)
{
    // for every block in the buffer...
    // get words from the buffer
    // and sum the number of words of a similar length

    char *line;
    int length = 0;

    // stack to store array of chars making up a word
    Stack *stack = malloc(sizeof(Stack));
    stack->size = 0;
    stack->capacity = MAX_LINE_LENGTH - 1;
    // stack->array = 0;

    // while blocks can be read from the buffer
    while ((line = getConcurrentBuffer(buffer)) != NULL)
    {
        // for every char in the block
        for (int i = 0; i < strlen(line); i++)  // check if line is not NULL
        {
            // if line[i] is a letter
            // in future, check if char's encoding is within a-z
            if (((line[i] >= 'A') && (line[i] <= 'Z')) || ((line[i] >= 'a') && (line[i] <= 'z')))
            if (line[i] != ' ' && line[i] != '\'' && line[i] != '-' && line[i] != '\"' && line[i] != '.' && line[i] != ',')
            {
                // add each line[i] to a stack
                stack->size++;
                stack->array[stack->size] = line[i];
                
                #if DEBUG
                    printf("letter: %c\n", line[i]);
                #endif
            }

            // if line[i] is not a letter
            if (line[i] == ' ' || line[i] == '\'' || line[i] == '-' || line[i] == '\"' || line[i] == '.' || line[i] == ',')
            {
                #if DEBUG
                    printf("letter: \n");
                #endif

                // word is whatever was on the stack before the non-letter was read
                // thus the length is the size of the stack minus one
                length = stack->size;

                // pop off whole stack
                for (int j = 0; stack->size != 0; j++)
                {
                    // pop each entry
                    // forget element is in the stack to be written over later
                    stack->size--;
                }   
            }

            // if the length is sufficient, increment word count array/histogram 
            // at length index (global array of ints to store length occurences)
            if (length > 5 && length < 51)
            {
                #if DEBUG
                    printf("\tlength: %d\n", length);
                #endif

                // lock histogram
                pthread_mutex_lock(&mu);

                // increment the global histogram array at index
                histogram[length]++;

                // unlock histogram
                pthread_mutex_unlock(&mu);

                // reset length for next word
                length = 0;
            }
        }

        free(line);
    }

    // deallocate memory
    free(stack);    // fix stack implementation
    deleteConcurrentBuffer(buffer);

    // maybe return the global histogram array
    return NULL;
}
