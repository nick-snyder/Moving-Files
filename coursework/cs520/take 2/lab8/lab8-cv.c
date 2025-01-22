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

int numDoneThreads;              /* Counter for exiting children */

int sum;                        /* Global sum of areas */

int n;                          /* Number of threads to create */

char *indexArray[MAX_T]; // index array

void usage(char *);

void error(char *);

void *work(void *);

// holds the filename
// typedef struct Argument
// {
//     char *filename;
// }
// Argument;

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

    numDoneThreads = 0;   // number of children that have exited

    sum = 0;

    // printf("n: %d\n", n);

    for (i = 0; i < n; i++)
    {
        // printf("%ld\n", i);
        indexArray[i] = argv[i+1];
        // printf("filename: %s\n", indexArray[i]);

        // create threads; DANGER: thread logical id (int) passed as void*
        if (pthread_create(&pt[i], NULL, work, (void *) i) != 0)
        {
            error("error in thread create");
        }
    }   

    // need a loop here because of possible spurious wakeup from
    // pthread_cond_wait

    // while not all threads are done
    while (numDoneThreads < n)
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
    long i = (long) in;

    // int a = indexArray[]

    // n = n;
    // int b = 0;
    // for (int j = 0; j < *indexArray[j]; j++)
    // {
        
    // }
    int j = 0;
    while (indexArray[j] != NULL)
    {
        // b++;
        j++;
    }
    // printf("b: %d\n", b);
    
    if (i > -1)
    {
        char *filename = indexArray[i];
        FILE* file = fopen(filename, "r");
        if (!file)
        {
            printf("%s=%d\n", filename, localSum);
            
            // increment done thread count
            numDoneThreads++;

            // if all child threads are done
            if (numDoneThreads == j)
            {
                // wakeup parent thread
                if (pthread_cond_signal(&cv) != 0)
                {
                    error("error in cond_signal");
                }   
            }

            return 0;
        }
        // printf("file: %s\n", filename);

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
    }

    // lock 
    if (pthread_mutex_lock(&mu) != 0)
    {
        error("error in mutex_lock");
    }
    
    // add to global sum
    sum += localSum;

    // increment done thread count
    numDoneThreads++;

    // printf("numDoneThreads: %d\n", numDoneThreads);
    // printf("n: %d\n", n);

    // printf("j: %d\n", j);

    // if all child threads are done
    if (numDoneThreads == j)
    {
        // wakeup parent thread
        if (pthread_cond_signal(&cv) != 0)
        {
            error("error in cond_signal");
        }   
    }

    // unlock
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
