/**
 * CS515 Assignment 4
 * File: queue.cpp
 * Name: Nick Snyder
 * Section: 2
 * Date: 1 March 2022
 * Collaboration Declaration: online resources
 */

#include "queue.h"
#include <iostream>

// constructor with default capacity value
queue::queue(int c)
: _arr(0), _capacity(c), _front(0)
{
    _arr = new TYPE[_capacity];
	for(int i = 0; i < _capacity; i++)
		_arr[i] = 0;
}

// copy constructor
queue::queue(const queue& other)
: _capacity(other._capacity), _front(other._front)
{
    _arr = new TYPE[_capacity];
    int rear = (_front + _size) % _capacity - 1;
    for (int i = _front; i < rear; i++)
        _arr[i] = other._arr[i];
}

// assignment operator
queue& queue::operator=(const queue& other) {
    // if they are identical
    if (this == &other)
        return *this;

    delete[] _arr;
    _capacity = other._capacity;
    _front = other._front;

    _arr = new TYPE[_capacity];
    int rear = (_front + _size) % _capacity - 1;
    for (int i = _front; i < rear; i++)
        _arr[i] = other._arr[i];
    return *this;
}

// destructor
queue::~queue() {
    delete[] _arr;
}

// add an element to the end of queue (expand if necessary)
void queue::enqueue(const TYPE x) {
    // initialize rear for later reference
    int rear = (_front + _size) % _capacity;

    // if queue is full, expand the queue
    if (size() == _capacity) {
        // create new queue with _capacity * 2
        _capacity *= 2;
        TYPE *tempArr = new TYPE[_capacity];

        // print array before expansion
        // std::cout << "Old array ";
        // for (int t = 0; t < _capacity / 2; t++)
        //     std::cout << _arr[t] << " ";
        // std::cout << std::endl;

        // fill temp array with old array values
        int i;
        for (i = 0; i < size() - _front; i++) {
            //std::cout << "Adding: " << _arr[i + _front] << " to new array at position " << i << std::endl;
            tempArr[i] = _arr[i + _front];
        }
        for (int j = 0; j < _front; j++) {
            //std::cout << "Adding: " << _arr[j] << " to new array at position " << j << std::endl;
            tempArr[i] = _arr[j];
            i++;
        }

        // print array after expansion
        // std::cout << "New array ";
        // for (int t = 0; t < _capacity; t++)
        //     std::cout << tempArr[t] << " ";
        // std::cout << std::endl;

        // delete old array and replace it with temp array
        delete[] _arr;
        _arr = tempArr;
        _front = 0;
        rear = size() - 1;
    }
    // add to queue
    _arr[rear] = x;
    _size++;


}

// remove an element from the front of queue
TYPE queue::dequeue() {
    if (empty())
        throw EmptyQueueException();
    TYPE ret = _arr[_front];
    _arr[_front] = 0;
    _front++;
    _size--;
    return ret;
}

// access the element at queue front; does not remove the element
TYPE& queue::front() {
    return _arr[_front];
}

// return true if the queue is empty, false otherwise
bool queue::empty() {
    return size() == 0;
}

// return the number of elements currently in the queue
int queue::size() {
    return _size;
}

// return the current capacity of the queue
int queue::capacity() {
    return _capacity;
}

// output queue elements from queue front to queue end
// elements are separated with a white space.
void queue::dump(ostream &os) {
    int rear = (_front + _size) % _capacity;

    os << "Current array: ";
    for (int t = 0; t < _capacity / 2; t++)
        os << _arr[t] << " ";
    os << std::endl;

    // for (int i = _front; i < rear; i++)
    //     os << _arr[i] << " ";
    // os << std::endl;
}
