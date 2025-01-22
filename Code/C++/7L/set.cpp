#include "set.h"
#include <queue>
#include <bits/stdc++.h>

// default constructor; constructs empty set
Set::Set():_size(0){
    // create a dummy root node
    _root = new Elem;
    _root->info = numeric_limits<int>::max();
    _root->left = _root;  // empty tree
    _root->right = 0;
    _root->rightThread = false;
}

// destructor
Set::~Set(){
    if (_root->left != _root)  // not an empty tree
        destructCode(_root->left);
    delete _root;
}

// common destruct code
void Set::destructCode(Elem *& p) {

    if (!p)
        return;

    destructCode(p->left);

    if (!p->rightThread)
        destructCode(p->right);

    delete p;
    p = nullptr;
}

// returns true if the new node is inserted, otherwise false
bool Set::insert(ELEMENT_TYPE v){
    if (insert(_root->left, v, _root)){
        _size++;
        return true;
    }
    return false;
}

// insert helper method
// returns true if the new node is inserted, otherwise false
bool Set::insert(Elem *&cur, const ELEMENT_TYPE &value, Elem *lastLeft){
    if (cur == _root || cur == 0) {
        cur = new Elem;
        cur->info = value;
        cur->left = 0;
        cur->right = lastLeft;
        cur->rightThread = true;
        return true;
    }
    
    if (value == cur->info){
        return false;
    }
    // insert at left
    if (value < cur->info)
        return insert( cur->left, value, cur);
    
    // insert at right
    if (!cur->rightThread){
        return insert(cur->right, value, lastLeft);
    } else {  // current's right is a thread; add a new node
        cur->rightThread = false;
        cur->right = new Elem;
        cur->right->info = value;
        cur->right->left = 0;
        cur->right->right = lastLeft;
        cur->right->rightThread = true;
        return true;
    }
}

// print out tree elements in depth first in order
void Set::depthFirstInOrder(){

    // Start at actual root(_root) or logical root(_root->left)
    Elem *e = _root;

    // Walk to left-most node
    while (e->left)
        e = e->left;

    // and process it (only used to print '3')
    std::cout << e->info << " ";

    while (e->right && e->right != _root) {
        
        // if node has a successor
        if (e->rightThread) {

            // process right node (moves to right node but prints it later)
            e = e->right;

        } else {

            // follow right pointer
            if (e->right)
                e = e->right;

            // Walk to left-most node (copy of step 1)
            while (e->left)
                e = e->left;
        }

        // prints node
        std::cout << e->info << " ";
    }
}

// Breadth first traverse
void Set::breadthFirst() {

    // make a queue
    queue<Elem> q;

    // make node at root
    Elem *e = _root->left; 
    q.push(*e);

    while (!q.empty()) {
        *e = q.front();
        q.pop();
        std::cout << e->info << " ";
        if (e->left)
            q.push(*e->left);
        if (!e->rightThread)
            q.push(*e->right);
    }
}

int Set::size() const{
    return _size;
}

// output the structure of tree. The tree is output as "lying down"
// in which _root is the LEFT most Elem.
void Set::printTree(ostream& out, int level, Elem *p){
    int i;
    if (p) {
        if (p->right && !p->rightThread)
            printTree(out, level+1,p->right);
        for(i=0;i<level;i++)
            out << "\t";
        out << p->info << '\n';
        printTree(out, level+1,p->left);
    }
}

// outputs information in tree in inorder traversal order
ostream& Set::dump(ostream &out){
    if ( _root == _root->left) // tree empty
        return out;
    printTree(out, 0, _root->left);   // print tree structure
    return out; 
}

// outputs using overloaded << operator
ostream& operator << (ostream &s, Set &v){
    v.dump(s);
    return s;
}
