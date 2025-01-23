// (Uses Posix threads on Linux)
// child threads update global sum using mutex to protect the update
// thread_join used to have main thread wait
// main thread then prints the global sum

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

// the maximum number of child threads that can be used
#define MAX_T 12

// global sum, update by threads using mutex to protect
int sum;

// array for storing thread IDs
pthread_t pt[MAX_T];

// mutex to protect update to global sum
pthread_mutex_t mu;

// prints usage message if command line arguments are not what is expected
// program expects a single argument: the number of child threads to create
void usage(char *);

// prints an error message and terminates the program
void error(char *);

// this is the work executed by each child thread
void *work(void *);

// holds the filename
typedef struct Argument
{
    char *filename;
}
Argument;

int main (int argc, char *argv[])
{
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

    // initialize global sum
    sum = 0;

    // initialize mutex to protect global sum
    if (pthread_mutex_init(&mu, NULL) != 0)
    {
        error("can't init mutex");
    }
    
    // create n threads
    for (i = 0; i < n; i++)
    {
        // Make a struct that holds the filename
        Argument *inputFile = malloc(sizeof(Argument));
        if (!inputFile)
        {
            return 0;
        }

        inputFile->filename = argv[i+1];

        /* create threads; DANGER: thread logical id (int) passed as "void *" */
        if (pthread_create(&pt[i], NULL, work, (void *) inputFile) != 0)
        {
            error("error in thread create");
        }
    }

    // wait for each thread to finish
    for (i = 0; i < n; i++)
    {
        if (pthread_join(pt[i], NULL))
        {
            error("error in thread join");
        }
    }

    // output
    printf("Total Count=%d\n", sum);

    return 0;
}

void *work(void *in)
{
    Argument *inputFile = in;
    char *filename = inputFile->filename;
    int localSum = 0;

    FILE* file = fopen(filename, "r");
    if (!file)
    {
        return 0;
    }
    
    unsigned char line = getc(file);
    while (line != (unsigned char) EOF)
    {
        if (line == 0x0A) 
        {
            localSum++;
        }
        line = getc(file);
    }    

    if (pthread_mutex_lock(&mu) != 0)
    {
        error("error in mutex_lock in child");
    }

    sum += localSum;

    if (pthread_mutex_unlock(&mu) != 0)
    {
        error("error in mutex_unlock in child");
    }

    printf("%s=%d\n", filename, localSum);
    fclose(file);
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

