/**
 * CS515 Lab 6
 * File: PQueue0.cpp
 * Name: Nick Snyder
 * Section: 2
 * Date: 8 March 2022
 * Collaboration Declaration: online resources
 */

#include "PQueue.h"

// default constructor, construct an empty heap
template<class T, int MAX_SIZE>
PQueue<T, MAX_SIZE>::PQueue() : _size(0) {
    _array[MAX_SIZE + 1];
    for (int i = 0; i < MAX_SIZE + 1; i++)
        _array[i] = 0;
}

// construct a heap from an array of elements;
template<class T, int MAX_SIZE>
PQueue<T, MAX_SIZE>::PQueue(T* items, int size) : _size(0) {
    for (int i = 0; i < size; i++)
        insert(items[i]);
}

// insert an item; duplicates are allowed.
template<class T, int MAX_SIZE>
void PQueue<T, MAX_SIZE>::insert(T t) {
    _size++;
    _array[_size] = t;
    moveUp();
}

// return the smallest item from the queue
template<class T, int MAX_SIZE>
T PQueue<T, MAX_SIZE>::findMin() { return _array[1]; }

// remove the smallest item from the queue
template<class T, int MAX_SIZE>
void PQueue<T, MAX_SIZE>::deleteMin() {
    _array[1] = _array[_size];
    _size--;
    moveDown(1);
}

// test if the priority queue is logically empty
template<class T, int MAX_SIZE>
bool PQueue<T, MAX_SIZE>::isEmpty() { return (size() == 0); }

// return queue size
template<class T, int MAX_SIZE>
int PQueue<T, MAX_SIZE>::size() { return _size; }

// linear heap construction
template<class T, int MAX_SIZE>
void PQueue<T, MAX_SIZE>::buildHeap() {
    for (int i = _size / 2; i > 0; i--)
        moveDown(i);
}

// move down element at given child
template<class T, int MAX_SIZE>
void PQueue<T, MAX_SIZE>::moveDown(int currentNode) {
    int leftChild = currentNode * 2;
    int rightChild = leftChild + 1;
    while ((currentNode < _size / 2 + 1) && ((_array[currentNode] > _array[leftChild]) || (_array[currentNode] > _array[rightChild]))) {
        if (_array[leftChild] < _array[rightChild]) {
            swap(_array[currentNode], _array[leftChild]);
            currentNode *= 2;
        } else {
            swap(_array[currentNode], _array[rightChild]);
            currentNode = currentNode * 2 + 1;
        }
        leftChild = currentNode * 2;
        rightChild = leftChild + 1;
    }
}

// move up the last element in the heap array
template<class T, int MAX_SIZE>
void PQueue<T, MAX_SIZE>::moveUp() {
    int child = _size;
    while ((child > 1) && (_array[child / 2] > _array[child])) {
        swap(_array[child], _array[child / 2]);
        child /= 2;
    }
}

template<class T, int MAX_SIZE>
void PQueue<T, MAX_SIZE>::to_string() {
    for (int i = 1; i < _size; i++) {
        std::cout << _array[i] << " < ";
    }
    std::cout << std::endl;
}
