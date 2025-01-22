/** 
 * CS515 Assignment 6
 * File: set.cpp
 * Name: Nick Snyder
 * Section: 2
 * Date: 28 March 2022
 * Collaboration Declaration: online resources 
 */

#include "set.h"
#include <iostream>

// constructs empty set
Set::Set()
{
    _head = new Elem;
    _tail = new Elem;

    _head->next = _tail;
    _tail->prev = _head;

    _size = 0;
} 

// copy constructor
Set::Set(const Set &rhs) {

    _head = new Elem;
    _tail = new Elem;

    _head->next = _tail;
    _tail->prev = _head;

    _size = 0;

    copyCode(rhs);
} 

// destructor
Set::~Set() {
    //destructCode();
}

// assignment operator
Set& Set::operator=(const Set &rhs) {
    if (this != &rhs) {
        destructCode();
        copyCode(rhs);
    }
    return *this;
}

//-----Basic operations-----

// insert an element
void Set::insert(ELEMENT_TYPE t) {
    // check find() returns s.end()
    if (this->find(t) == this->end()) {

        // insert where fits
        //std::cout << "HERE\n";

        if (size() == 0) {
            Elem *n = new Elem();
            n->info = t;
            n->next = _tail;
            n->prev = _head;
            _head->next = n;
            _tail->prev = n;
        } else {  
            Elem *e = _head;
            while (e->info < t && e != _tail)
                e = e->next;
            Elem *n = new Elem();
            n->info = t;
            n->next = e;
            n->prev = e->prev;
            e->prev->next = n;
            e->prev = n;
        }
        _size++;
    }
}

// remove an element from the set
void Set::erase(ELEMENT_TYPE t) {

    // find element at iterator
    Iterator it = this->find(t);
    if (it != this->end()) {
        Elem *e = _head;
        while (e->info != t)
            e = e->next;

        e->prev->next = e->next;
        e->next->prev = e->prev;
        // remove element at iterator
        _size--;
    }
}

// remove all elements from set
void Set::clear() {
    for (Set::Reverse_Iterator rit = this->rbegin(); rit != this->rend(); rit++)
        erase(*rit);
}

// return size of the set
int Set::size() const {
    return _size;
}




//-----Iterators-----

// return an iterator to the element if val is found, or set::end() otherwise.
Set::Iterator Set::find(ELEMENT_TYPE t) const {
    for (Set::Iterator it = this->begin(); it != this->end(); it++) {
        //std::cout << "HERE\n";
        if (*it == t) {
            //std::cout << "WHERE\n";

            return it;
        }
    }
    return this->end();
}

// return an iterator pointing at the begining of the list
Set::Iterator Set::begin() const {
    Iterator it (_head->next);
    return it;
}

// return an iterator pointing at one element beyond the end of list
Set::Iterator Set::end() const {
    Iterator it (_tail);
    return it;
}

// return an reverse iterator pointing at the reverse beginning of the list
Set::Reverse_Iterator Set::rbegin() const {
    Reverse_Iterator rit (_tail->prev);
    return rit;
}

// return an reverse iterator pointing at one element beyond the beginning of list
Set::Reverse_Iterator Set::rend() const {
    Reverse_Iterator rit (_head);
    return rit;
}

// friend top level function for output all list elements
// elements are output as a single white space delimited 
ostream& operator<< (ostream& out, Set& s) {
    for (Set::Iterator it = s.begin(); it != s.end(); it++)
        out << *it << " ";
    return out;
}




// construct a null iterator
Set::Iterator::Iterator() {
    _cur = NULL;
} 

// construct an iterator given pointer to Elem
Set::Iterator::Iterator(Elem *cur) {
    this->_cur = cur;
}  

//-----Overloaded operators-----

//dereference
ELEMENT_TYPE& Set::Iterator::Iterator::operator*() {
    return _cur->info;
} 

//post-increment operator
Set::Iterator Set::Iterator::operator++(int) {
    Iterator result = *this;
    //if (_cur)
    _cur = _cur->next;  
    return result;
} 

//post-decrement operator
Set::Iterator Set::Iterator::operator--(int) {
    Iterator result = *this;
    if (_cur)
        _cur = _cur->prev;
    return result;
} 

// equality operator
bool Set::Iterator::Iterator::operator==(Iterator it) const {
    return _cur == it._cur;
} 

// inequality operator
bool Set::Iterator::Iterator::operator!=(Iterator it) const {
    return _cur != it._cur;
} 




// construct a null iterator
Set::Reverse_Iterator::Reverse_Iterator() {
    _cur = NULL;
} 

// construct an iterator given pointer to Elem 
Set::Reverse_Iterator::Reverse_Iterator(Elem *cur) {
    this->_cur = cur;
} 

//-----Overloaded operators-----

//dereference
ELEMENT_TYPE& Set::Reverse_Iterator::Reverse_Iterator::operator*() {
    return _cur->info;
} 

//post-increment operator
Set::Reverse_Iterator Set::Reverse_Iterator::operator++(int) {
    Reverse_Iterator result = *this;
    if (_cur)
        _cur = _cur->prev;
    return result;
} 

//post-decrement operator
Set::Reverse_Iterator Set::Reverse_Iterator::operator--(int) {
    Reverse_Iterator result = *this;
    if (_cur)
        _cur = _cur->next;
    return result;
} 

// equality operator
bool Set::Reverse_Iterator::Reverse_Iterator::operator==(Reverse_Iterator rit) const { 
    return _cur == rit._cur;
} 

// inequality operator
bool Set::Reverse_Iterator::Reverse_Iterator::operator!=(Reverse_Iterator rit) const {
    return _cur != rit._cur;
}




// common code for copy constructor and assignment
void Set::copyCode(const Set & v) {
    // iterate through
    for (Set::Iterator it = v.begin(); it != v.end(); it++)
        insert(*it);
        // copy iterator reference to new location in Set
}

// common code for deallocation
void Set::destructCode() {
    // iterate through
    Elem *e = _tail;
    for (Set::Reverse_Iterator rit = this->rbegin(); rit != this->rend(); rit++)
        this->Set::erase(*rit);
        // delete iterator reference
}

// output set elements
ostream& Set::dump(ostream& out, const Set &v) {
    // iterate through
    for (Set::Iterator it = v.begin(); it != v.end(); it++)
        out << *it;
        // print out each iterator reference
    return out;
}





// set intersect
Set operator&(const Set& s1, const Set& s2) {

    Set s;

    for (Set::Iterator it1 = s1.begin(); it1 != s1.end(); it1++) {
        for (Set::Iterator it2 = s2.begin(); it2 != s2.end(); it2++) {
            if (*it1 == *it2) {
                s.insert(*it2);
            }
        }
    }

    return s;
}

// set union
Set operator|(const Set& s1, const Set& s2) {

    Set s;

    for (Set::Iterator it1 = s1.begin(); it1 != s1.end(); it1++)
        s.insert(*it1);

    for (Set::Iterator it2 = s2.begin(); it2 != s2.end(); it2++)
        s.insert(*it2);

    return s;
}

// set difference 
Set operator-(const Set& s1, const Set& s2) {

    Set s;

    // check every value of one set
    // find() on each dereferenced iterator against first set;

    for (Set::Iterator it1 = s1.begin(); it1 != s1.end(); it1++) {
        s.insert(*it1);
    }

    for (Set::Iterator it2 = s2.begin(); it2 != s2.end(); it2++) {
        if (s2.find(*it2) != s2.end())
            s.erase(*it2);
        else 
            s.insert(*it2);
    }

    return s;
}

// set equality
bool operator==(const Set& s1, const Set& s2) {
    bool boolean = false;
    Set::Iterator it1 = s1.begin();
    Set::Iterator it2 = s2.begin();

    while ((*it1 == *it2) && (it1 != s1.end())) {
        it1++;
        it2++;
        boolean = true;
    }

    return boolean;
}