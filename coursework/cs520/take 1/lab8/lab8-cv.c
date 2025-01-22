// (Uses Posix threads on Linux)
//
// This version uses a mutex and condition variable to coordinate
// update to a shared variable and to communicate to the parent
// thread when all child threads are done. Also the parent does
// part of the work. It acts like child 0.

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_T 12

pthread_t pt[MAX_T];

pthread_mutex_t mu;             /* Mutex for "sum" and "bar_cnt" */

pthread_cond_t cv;              /* Condition variable to hold parent until all children done */

int cnt;                        /* Counter for exiting children */

int sum;                        /* Global sum of areas */

int n;                          /* Number of threads to create */

void usage(char *);

void error(char *);

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

    if (pthread_mutex_init(&mu, NULL) != 0)
    {
        error("can't init mutex");
    }

    if (pthread_cond_init(&cv, NULL) != 0)
    {
        error("can't init condition variable");
    }

    cnt = 0;   // number of children that have exited

    sum = 0;

    for (i = 1; i <= n; i++)
    {
        // Make a struct that holds the filename
        Argument *inputFile = malloc(sizeof(Argument));
        if (!inputFile)
        {
            return 0;
        }

        inputFile->filename = argv[i];

        // create threads; DANGER: thread logical id (int) passed as void*
        if (pthread_create(&pt[i], NULL, work, (void *) inputFile) != 0)
        {
            error("error in thread create");
        }
    }   
    
    printf("HERE\n");
    // work(0);  

    cnt += 1;

    // need a loop here because of possible spurious wakeup from
    // pthread_cond_wait
    while (cnt < n)
    {
        // wait for all children to finish
        if (pthread_cond_wait(&cv, &mu) != 0)
        {
            error("error in cond_wait by parent");
        }   
    }

    // output
    printf("Total Count=%d\n", sum);

    return 0;
}

void *work(void *in)
{
    int localSum = 0;
    long id = (long) in;          /* Logical thread id (0..n-1) */

    if (in)
    {
        Argument *inputFile = in;
        char *filename = inputFile->filename;

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

        printf("%s=%d\n", filename, localSum);
        fclose(file);
        free(inputFile); 
    }

    if (pthread_mutex_lock(&mu) != 0)
    {
        error("error in mutex_lock");
    }
    
    sum += localSum;

    if (id == 0)  // parent continues to hold lock!
    {
        return 0;
    }

    if (++cnt == n)  // all threads are now done
    {
        if (pthread_cond_signal(&cv) != 0)  // wakeup parent
        {
            error("error in cond_signal");
        }   
    }

    if (pthread_mutex_unlock(&mu) != 0)
    {
        error("error in mutex_unlock");
    }
    
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
