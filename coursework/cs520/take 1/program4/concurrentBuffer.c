//
// defines a concurrent buffer that supports the producer-consumer pattern
//
// the buffer elements are simply void* pointers
// note: the buffer does not make a copy of the data.
//       it simply stores a pointer to the data.
// 
// the buffer is FIFO (first in, first out)
//

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "concurrentBuffer.h"

#define DEBUG 0

// To Do:
    // show errors better
    // fix problem where it runs forever in valgrind
    // add better blocking mechanism. maybe

typedef struct ConcurrentBuffer
{
    int front;      // index where blocks are taken
    int rear;       // index where blocks are put
    int size;       // number of blocks currently in buffer
    int capacity;   // capacity of array
    void** array;   // circular queue

    pthread_mutex_t mu;             /* Mutex for "sum" and "bar_cnt" */
    pthread_cond_t cv;              /* Condition variable to hold parent until all children done */
}
ConcurrentBuffer;

// create a concurrent buffer
//   size: the number of elements in the buffer
//   returns: a handle to be used to operate on the buffer

// creates an instance of a concurrent buffer with the
// number of buffer elements given by the argument "size". 
// The buffer is initialized to be empty. If successful, 
// the function returns a non-NULL void* "handle" which 
// can  be passed to the other three functions in order to 
// operate  on the buffer. If the "size" argument is zero, 
// then the function will return NULL, indicating failure. 
// If sufficient memory cannot be allocated for the buffer, 
// then the function will also return NULL
void *createConcurrentBuffer(unsigned int size)
{
    if (size == 0)
    {
        return NULL;
    }
    
    ConcurrentBuffer *buffer = malloc(sizeof(ConcurrentBuffer));
    if (!buffer)
    {
        return NULL;
    }

    buffer->array = calloc(size, sizeof(void*));
    if (!buffer->array)
    {
        free(buffer);
        return NULL;
    }

    buffer->front = 0;
    buffer->rear = 0;
    buffer->size = 0;
    buffer->capacity = size;

    pthread_mutex_init(&buffer->mu, NULL);
    pthread_cond_init(&buffer->cv, NULL);
    
    return buffer;
}

// put a value in a buffer
//   handle: handle for a concurrent buffer
//   p: pointer to be put in the buffer
//   note: calling thread will block until there is space in the buffer

// puts a pointer to a value into the buffer indicated by the
// "handle" argument. If the buffer is full, the calling 
// thread will block until space becomes available. If a NULL 
// "handle" is passed in, the function will print an 
// appropriate error message to stderr and the program is 
// terminated via exit(-1)
void putConcurrentBuffer(void *handle, void *p)
{
    ConcurrentBuffer *buffer = handle;

    // if a NULL handle is passed in
    if (!buffer)
    {
        // print appropriate error message
        exit(-1);
    }

    // lock the buffer while block is added to buffer
    pthread_mutex_lock(&buffer->mu);

    // while buffer is full
    while (buffer->size == buffer->capacity)
    {

        #if DEBUG
            printf("waiting until not full...\n");
        #endif

        // wait for buffer to not be full
        pthread_cond_wait(&buffer->cv, &buffer->mu);
    }

    buffer->rear = (buffer->rear + 1) % buffer->capacity;
    buffer->array[buffer->rear] = p;
    buffer->size++;

    #if DEBUG  
        printf("~%p~ was just added to the buffer\n", p);
    #endif

    // unlock buffer when done
    pthread_mutex_unlock(&buffer->mu);

    // send signal that consumer is able to get blocks
    pthread_cond_signal(&buffer->cv);
}

// get a value from a buffer
//   handle: handle for a concurrent buffer
//   returns: pointer retrieved from buffer
//   note: calling thread will block until there is a value available

// retrieves a pointer to a value from the buffer indicated by the 
// "handle" argument. If the buffer is empty, the calling thread 
// will block until a pointer to a value becomes available. The 
// retrieved pointer is returned by the function. If a NULL 
// "handle" is passed in, the function will print an appropriate 
// error message to stderr and the program is terminated via 
// exit(-1)
void *getConcurrentBuffer(void *handle)
{
    ConcurrentBuffer *buffer = handle;
    void *block;

    // if a NULL handle is passed in
    if (!buffer)
    {
        // print appropriate error message
        exit(-1);
    }

    // lock buffer to safely remove block
    pthread_mutex_lock(&buffer->mu);

    // while buffer is empty
    while (buffer->size == 0)
    {
        #if DEBUG
            printf("waiting until not empty...\n");
        #endif

        // wait for buffer to have at least one block in it
        pthread_cond_wait(&buffer->cv, &buffer->mu);
    }
    
    // saving data from buffer array and moving front and rear indecies
    // data saved from buffer doesn't get removed, just forgotten
    buffer->front = (buffer->front + 1) % buffer->capacity;
    block = buffer->array[buffer->front];
    buffer->size--;

    #if DEBUG
        printf("~%p~ was just taken from the buffer\n", block);
    #endif

    // unlock buffer when done
    pthread_mutex_unlock(&buffer->mu);

    // send signal that producer can put blocks
    pthread_cond_signal(&buffer->cv);
    
    // return block of text
    return block;
}

void deleteConcurrentBuffer(void *handle)
{
    ConcurrentBuffer *buffer = handle;

    pthread_mutex_destroy(&buffer->mu);
    pthread_cond_destroy(&buffer->cv);
    free(buffer->array);
    free(buffer);    
}