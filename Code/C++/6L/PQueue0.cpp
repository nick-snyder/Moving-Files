/**
 * CS515 Lab 6
 * File: PQueue0.cpp
 * Name: Nick Snyder
 * Section: 2
 * Date: 8 March 2022
 * Collaboration Declaration: online resources
 */

#include "PQueue0.h"

// default constructor, construct an empty heap
PQueue::PQueue() : _size(0) {
    //_size = 0;
    _array[MAX_SIZE + 1];
    for (int i = 0; i < MAX_SIZE + 1; i++)
        _array[i] = 0;
}

// construct a heap from an array of elements;
PQueue::PQueue(int* items, int size) : _size(0) {

    for (int i = 0; i < MAX_SIZE + 1; i++)
        _array[i] = 0;
    for (int i = 0; i < size; i++)
        insert(items[i]);
    //     _array[i] = items[i];
    //     _size++;
    // }
    // buildHeap();
}

// insert an item; duplicates are allowed.
void PQueue::insert(T t) {

    _size++;
    _array[_size] = t;

    moveUp();
}

// return the smallest item from the queue
T PQueue::findMin() {
    return _array[1];
}

// remove the smallest item from the queue
void PQueue::deleteMin() {

    _array[1] = _array[_size];
    _size--;

    moveDown(1);
}

// test if the priority queue is logically empty
bool PQueue::isEmpty() {
    return (size() == 0);
}

// return queue size
int PQueue::size() {
    return _size;
}

// linear heap construction
void PQueue::buildHeap() {

    for (int i = _size / 2; i > 0; i--)
        moveDown(i);
}

// move down element at given index
void PQueue::moveDown(int tmp) {

    // left child of tmp
    int l = 2 * tmp;

    // right child of tmp
    int r = l + 1;

    while ((tmp < _size / 2 + 1) && ((_array[tmp] > _array[l]) || (_array[tmp] > _array[r]))) {

        // if the left child is less than the right child
        if (_array[l] < _array[r]) {

            // swap two numbers
            swap(_array[tmp], _array[l]);

            // make the left child the new tmp
            tmp *= 2;

        } else {

            // swap two numbers
            swap(_array[tmp], _array[r]);

            // make the right child the new tmp
            tmp = tmp * 2 + 1;
        }

        // update left child
        l = 2 * tmp;

        // update right child
        r = l + 1;
    }
}

// move up the last element in the heap array
void PQueue::moveUp() {

    // int child = _array[_size];
    // int parent = child / 2;


    int index = _size;
    while (index > 1 && _array[index / 2] > _array[index]) {
        T val = _array[index];
        _array[index] = _array[index / 2];
        _array[index / 2] = val;
        index = index / 2;
    }


    // while (parent > 0) {
    //     if (_array[parent] > _array[child]) {
    //         swap(_array[parent], _array[child]);
    //         child = parent;
    //         parent /= 2;
    //     }
    // }
}
