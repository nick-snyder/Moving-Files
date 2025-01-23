// Program with simple threads (no lock mechanism used, 
// each thread updates the count of the newlines for the 
// filename it receives in a location that is not shared, 
// can be its own copy of an array element that other 
// threads don’t use). The main() function tallies up the 
// total after all threads complete before printing each 
// filename and count, as well as the total count.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

// the maximum number of child threads that can be used
#define MAX_T 12

// array for storing thread IDs
pthread_t pt[MAX_T];

// child threads drop values into the array
int books[MAX_T];

// prints usage message if command line arguments are not what is expected
// program expects a single argument: the number of child threads to create
void usage(char *);

// prints an error message and terminates the program
void error(char *);

// this is the work executed by each child thread
void *work(void *);

static int x = 0;

// holds the filename
typedef struct Argument
{
    char *filename;
    int index;
}
Argument;

// x threads are created
// each thread counts the line count of a book and puts the result in an array
// once all threads are done, the main thread prints out the array
int main (int argc, char *argv[])
{
    int sum = 0;
    long i;
    int n = argc - 1;

    if (n <= 0) 
    {
        usage("number of threads must be > 0");
    }
    
    if (n > MAX_T) 
    {
        usage("too many threads requested");
    }

    // printf("%d (child) threads used\n", n);

    // create n threads
    for (i = 1; i <= n; i++)
    {
        // Make a struct that holds the filename
        Argument *inputFile = malloc(sizeof(Argument));
        if (!inputFile)
        {
            return 0;
        }
        
        inputFile->filename = argv[i];
        inputFile->index = i;

        // printf("filename in main: %s\n", inputFile->filename);

        /* create threads; DANGER: thread logical id (int) passed as "void *" */
        if (pthread_create(&pt[i], NULL, work, (void *) inputFile) != 0)
        {
            error("error in thread create");
        }
        // free(inputFile);
    }

    // wait for each thread to finish
    for (i = 1; i <= n; i++)
    {
        if (pthread_join(pt[i], NULL))
        {
            error("error in thread join");
        }
        sum += books[i];
    }

    // output
    printf("Total Count=%d\n", sum);

    return 0;
}

void *work(void *in)
{
    Argument *inputFile = in;
    char *filename = inputFile->filename;
    int id = inputFile->index;
    int lineCount = 0;

    FILE* file = fopen(filename, "r");
    if (!file)
    {
        x++;
        printf("times a file failed to open: %d\n", x);
        return 0;
    }
    // printf("\tfilename in work: %s\n", filename);
    unsigned char line = getc(file);
    while (line != (unsigned char) EOF)
    {
        if (line == 0x0A) 
        {
            lineCount++;
        }
        line = getc(file);
    }    

    fclose(file);
    books[id] = lineCount;
    printf("%s=%d\n", filename, lineCount);
    free(inputFile);
    return 0;
}

void error(char *str)
{
    perror(str);
    exit(-1);
}

void usage(char *str)
{
   fprintf(stderr, "usage: %s\n",str);
   exit(-1);
}