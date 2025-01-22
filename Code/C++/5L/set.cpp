/**
 * CS515 Lab 5
 * File: set.cpp
 * Name Nick Snyder
 * Section: 2
 * Date: 6 March 2022
 * Collaboration declaration: online resources
 */

#include "set.h"

// constructs empty set
Set::Set() {
    _head = 0; //new Elem();
    _tail = 0; //new Elem();

    // _head->next = _tail;
    // _tail->prev = _head;

    _size = 0;
}

// copy constructor (you can call copyCode method)
Set::Set(const Set &rhs) {
    copyCode(rhs);
}

// destructor (you can call destructCode method)
Set::~Set() {
    destructCode();
}

// assignment operator (you can call destructCode and copyCode methods)
Set& Set::operator=(const Set &rhs) {
    if (this != &rhs) {
        copyCode(rhs);
        destructCode();
    }
    return *this;
}

// insert an int into the set;
void Set::insert(ELEMENT_TYPE t) {
    // check if value is not already in Set
    if (!find(t)) {
        //return;
        // Find place where value would fit
        
        Elem *e = _head;
        if (size() != 0) {
            std::cout << "HERE" << std::endl;
            while (e->info < t)
                e = e->next;
            // e is now at where t should go
        }
        

        // linkedlist insert t at e
        // make new Elem with info t
        Elem *newElem = new Elem;
        newElem->info = t;
        
        std::cout << newElem << std::endl;
        std::cout << newElem->next << std::endl;
        std::cout << e << std::endl;
        std::cout << e->next << std::endl;

        // Elem after newElem
        newElem->next = e->next;
        //e->next->prev = newElem;

        

        // Elem before newElem
        e->next = newElem;
        newElem->prev = e;

        newElem->next->prev = newElem;
        

        // increment _size
        _size++;

        // deallocate memory
        delete e;
        delete newElem;
    }
}

// remove an int from the set;
void Set::erase(ELEMENT_TYPE t) {
    // if value is in Set
    if (find(t)) {
        //return;
        // traverse linkedlist
        Elem *e = _head->next;
        while (e) {
            // check if each node is what we're looking for
            if (e->info == t) {
                // remove Node/Elem

                // reassign Elem pointers to skip over e
                e->prev->next = e->next;
                e->next->prev = e->prev;

                // decrement _size
                _size--;
                break;
            } 
        }
        // deallocate memory
        delete e;
    }
}

// remove all elements from set
void Set::clear() {
    Elem *e = _head;
    while (e) {
        e = e->next;
        delete _head;
        _head = e;
    }
    // deallocate memory
    delete e;
}

// return size of the set
int Set::size() const {
    return _size;
}

// return true if an element is found; false otherwise
bool Set::find(ELEMENT_TYPE t) const {
    // traverse linkedlist
    Elem *e = _head;
    while (e) {
        // check if each node is what we're looking for
        if (e->info == t) {
            // deallocate memory
            delete e;
            return true;
        }
    }
    // deallocate memory
    delete e;
    return false;
}

// common code for copy constructor and assignment operator
void Set::copyCode(const Set & v) {
    return;
    Set *tempSet = this;
    Elem *tempElem = tempSet->_head;
    Elem *vElem = v._head;

    // for every Elem in Set
    while (tempElem) {

        // assign v's Elem to this' Elem;
        tempElem->info = vElem->info;

        // iterate through Set
        tempElem = tempElem->next;
        vElem = vElem->next;
    }

    // deallocate memory
    delete tempSet;
    delete tempElem;
    delete vElem;
}

// common code for deallocation (destructor and assignment operator)
void Set::destructCode() {
    Elem *n = _head;
    while (n) {
        n = n->next;
        delete _head;
        _head = n;
    }
    // deallocate memory
    delete n;
}

// private method for output set elements
ostream& Set::dump(ostream& out, const Set &v) const {
    Elem *temp = _head->next;
    while (temp) {
        out << temp << " ";
        temp = temp->next;
    }
    // deallocate memory
    delete temp;

    return out;
}

// friend stand-alone functions
// logic equlity
bool operator==(const Set& s1, const Set& s2) {
    if (s1.size() == s2.size()) {
        Set::Elem *temp1 = s1._head->next;
        Set::Elem *temp2 = s2._head->next;
        
        while (temp1 != s1._tail) {
            
            if (temp1->info != temp2->info) {
                delete temp1;
                delete temp2;
                return false;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        delete temp1;
        delete temp2;
        return true;
    }
    return false;
}

// output operator
ostream& operator<< (ostream& out, const Set& s) {
    return out;
    Set::Elem *temp = s._head->next;
    while (temp != s._tail) {
        out << temp->info << " ";
        temp = temp->next;
    }
    delete temp;
    return out;
}
