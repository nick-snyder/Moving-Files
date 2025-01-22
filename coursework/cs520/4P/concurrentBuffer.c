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
#include <pthread.h>
#include <stdio.h>

#include "concurrentBuffer.h"

#define MAX_T 12
pthread_t pt[MAX_T];
pthread_mutex_t mu;

// Tasks
    // finish basic implementation
    // modify for use with threads
    // work on histogram.c

// Questions
    // what method of threading should be used?
    // what doest "blocking" look like?
    // is a circular queue better?

// #define MAX_Buffer_Size 

typedef struct Node
{
    void* data;
}
Node;

typedef struct ConcurrentBuffer
{
    int front;
    int rear;
    int size;       // capacity of array
    Node** array;   // circular queue
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

    buffer->array = calloc(size, sizeof(Node*));
    if (!buffer->array)
    {
        free(buffer);
        return NULL;
    }

    buffer->front = -1;
    buffer->rear = -1;
    buffer->size = size;
    
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
    // char *c = p;

    // if a NULL handle is passed in
    if (!buffer)
    {
        // print appropriate error message
        exit(-1);
    }

    Node *newNode = malloc(sizeof(Node*));
    if (!newNode)
    {
        return;
    }
    newNode->data = p;

    while (buffer->rear != -1 && (buffer->rear + 1) % buffer->size == buffer->front)
    {
        // printf("Buffer is full. Waiting for consumer...\n");
    }

    if (buffer->front == -1 && buffer->rear == -1)
    {
        buffer->front = 0;
        buffer->rear = 0;
        buffer->array[buffer->rear] = newNode->data;
    }
    else
    {
        buffer->rear = (buffer->rear + 1) % buffer->size;
        buffer->array[buffer->rear] = newNode->data;
    }    
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
    // printf("CONSOOMING\n");
    ConcurrentBuffer *buffer = handle;
    void *ret;

    // if a NULL handle is passed in
    if (!buffer)
    {
        // print appropriate error message
        exit(-1);
    }

    while (buffer->rear == -1)
    {
        // printf("Buffer is Empty. Waiting for producer...\n"); // wait for values
    }
    
    if (buffer->front == buffer->rear)
    {
        ret = buffer->array[buffer->front]; // returned
        // buffer->array[buffer->front]->data = NULL;
        buffer->front = -1;
        buffer->rear = -1;
    }    
    else
    {
        ret = buffer->array[buffer->front];
        // buffer->array[buffer->front]->data = NULL;
        buffer->front = (buffer->front + 1) % buffer->size;
    }

    return ret;
}

void deleteConcurrentBuffer(void *handle)
{
    ConcurrentBuffer *buffer = handle;

    for (int i = 0; i < buffer->size; i++)
    {
        
        free(buffer->array[i]);
    }
    free(buffer->array);
    free(buffer);    
}