/**
 * CS515 Lab 3
 * File: stack.cpp
 * Name: Nick Snyder
 * Section: 2
 * Date: 19 February 2022
 * Collaboration Declaration: online resources
 */

#include "stack.h"
#include <iostream>
using namespace std;

// constructor with default capacity value
stack::stack(int a) 
: _arr(0), _capacity(a), _tos(0)
{
    _arr = new TYPE[_capacity];
    for (int i = 0; i < _capacity; i++) {
        _arr[i] = 0;
    }
}
    
// copy constructor
stack::stack(const stack& other) 
: _capacity(other._capacity), _tos(other._tos), _arr(other._arr)
{
    _arr = new TYPE[_capacity];
    for (int i = 0; i < _capacity; i++)
        _arr[i] = other._arr[i];
}

// assignment operator
stack& stack::operator=(const stack& other)
{
    if (this == &other)
        return *this;
    delete[] _arr;
    _tos = other._tos; _capacity = other._capacity;
    if (_tos > 0) {
        _arr = new int[_tos];
        for (int i = 0; i < _tos; i++)
            _arr[i] = other._arr[i];
    }
    return *this;
}

// move constructor
stack::stack(stack&& other)
    //: _arr(std::move(other))
{  
    _capacity = other._capacity;
    _tos = other._tos;
    _arr = other._arr;

    other._capacity = INITCAP;
    other._tos = 0;
    other._arr = nullptr;
}

// move assignment operator
stack& stack::operator=(stack&& other)
{
    if (this != &other) 
    {
        delete[] _arr;

        _capacity = other._capacity;
        _tos = other._tos;
        _arr = other._arr;

        other._capacity = INITCAP;
        other._tos = 0;
        other._arr = nullptr;
    }
    return *this;
}

// destructor
stack::~stack() {
    delete[] _arr;
}

// push an element;
// if fixed sized stack, throw FullStackException when stack is full
void stack::push(const TYPE x) {
    if (_tos == _capacity - 1) {
        throw "FullStackException";
    } else {
        _arr[_tos] = x;
        _tos++;
    }
}

// remove and element; throw EmptyStackException when stack is empty
void stack::pop() {
    if (empty()) {
        throw "EmptyStackException";
    } else {
        _arr[top()] = 0;
        _tos--;
    }
}

// return a reference to the top element without popping; throw EmptyStackException when stack is empty
TYPE& stack::top() {
    if (empty()) {
        throw "EmptyStackException";
        return _tos;
    } else {
        return _arr[_tos];
    }
}

// return true if the stack is empty, false otherwise
bool stack::empty() {
    return size() == 0;
}

// return the number of elements currently on the stack
int stack::size() {
    return _tos;
}

// return the current capacity of the stack
int stack::capacity() {
    return _capacity;
}
