//
// defines a concurrent buffer that supports the producer-consumer pattern
//
// the buffer elements are simply void* pointers
// note: the buffer does not make a copy of the data.
//       it simply stores a pointer to the data.
//
// the buffer is FIFO (first in, first out)
//

// create a concurrent buffer
//   size: the number of elements in the buffer
//   returns: a handle to be used to operate on the buffer
void *createConcurrentBuffer(unsigned int size);

// put a value in a buffer
//   handle: handle for concurrent buffer
//   p: pointer to be put in the buffer
//   note: calling thread will block until there is space in the buffer
void putConcurrentBuffer(void *handle, void *p);

// get a value from a buffer
//   handle: handle for concurrent buffer
//   returns: pointer retrieved from buffer
//   note: calling thread will block until there is a value available
void *getConcurrentBuffer(void *handle);

// delete a buffer
//   handle: handle for the concurrent buffer to be deleted
void deleteConcurrentBuffer(void *handle);

