/**
 * CS515 Assignment 4
 * File: stack.cpp
 * Name: Nick Snyder
 * Section: 2
 * Date: 1 March 2022
 * Collaboration Declaration: online resources
 */

#include "stack.h"
#include <iostream>

// constructor with default capacity value
stack::stack(int c)
: _arr(0), _capacity(c), _tos(0)
{
    _arr = new TYPE[_capacity];
    for (int i = 0; i < _capacity; i++)
        _arr[i] = 0;
}

// copy constructor
stack::stack(const stack& other)
: _capacity(other._capacity), _tos(other._tos)//, _arr(other._arr)
{
    _capacity = other._capacity;
    _tos = other._tos;

    _arr = new TYPE[_capacity];
    for (int i = 0; i < _tos; i++)
        _arr[i] = other._arr[i];
}

// assignment operator
stack& stack::operator=(const stack& other) {
    // if they are identical
    if (this == &other)
        return *this;

    delete[] _arr;
    _tos = other._tos;
    _capacity = other._capacity;

    _arr = new TYPE[_capacity];
    for (int i = 0; i < _tos; i++)
        _arr[i] = other._arr[i];
    return *this;
}

// destructor
stack::~stack() {
    delete[] _arr;
}

// push an element, expanding if necessary;
void stack::push(const TYPE x) {
    if (size() >= _capacity) {
        _capacity *= 2;
        TYPE *tempArr = new TYPE[_capacity];
        for (int i = 0; i < _tos; i++)
            tempArr[i] = _arr[i];
        delete[] _arr;
        _arr = tempArr;
    }
    _arr[_tos] = x;
    _tos++;
}

// remove and element; throw EmptyStackException when stack is empty
void stack::pop() {
    if (empty())
        throw EmptyStackException();
    else {
        _arr[_tos] = 0;
        _tos--;
    }
}

// return a reference to the top element without popping; throw EmptyStackException when stack is empty
TYPE& stack::top() {
    if (empty())
        throw EmptyStackException();
    return _arr[_tos - 1];
}

// return true if the stack is empty, false otherwise
bool stack::empty() {
    return size() == 0;
}

// return the number of elements currently on the stack
int  stack::size() {
    return _tos;
}

// return the current capacity of the stack
int  stack::capacity() {
    return _capacity;
}

// output stack elements from stack top to stack bottom
// elements are separated with a white space.
void stack::dump(ostream &os) {
    for (int i = _tos - 1; i >= 0; i--)
        os << _arr[i] << " ";
    os << "\n";
}
