/**
 * CS515 Assignment 8
 * File: HuffTree.cpp
 * Name: Nick Snyder
 * Section: 2
 * Date: 7 April 2022
 * Collaboration Declaration: online resources
 */

#include "HuffTree.h"
#include "PQueue.h"
#include <string>

// get Huffman code and return it as a string
std::string HuffTree::getCode(char c) {
    return getCodeHelper(_root, c);
}

// build Huffman tree from an array of characters
// and and an array of their corresponding freqencys;
// the size of both arrays is given
void HuffTree::buildTree(char * chs, int * freqs, int size) {

    PQueue<HuffNode, 99> pq;

    for (int i = 0; i < size; i++) {

        HuffNode *in = new HuffNode(0, 0, freqs[i], chs[i]);
        pq.insert(*in);
        delete in;
    }

    while (pq.size() > 1) {

        HuffNode *left = new HuffNode(pq.findMin().left, pq.findMin().right, pq.findMin().freq, pq.findMin().data);
        pq.deleteMin();

        HuffNode *right = new HuffNode(pq.findMin().left, pq.findMin().right, pq.findMin().freq, pq.findMin().data);
        pq.deleteMin();

        HuffNode *hn = new HuffNode(left, right, left->freq + right->freq, '\0');
        pq.insert(*hn);
        delete hn;
    }

    _root = new HuffNode(pq.findMin().left, pq.findMin().right, pq.findMin().freq, pq.findMin().data);

    assignCodes(_root, "");
}

// destructor
HuffTree::~HuffTree() {
    deleteTree(_root);
}

// assign code to HuffNode already in HuffTree
void HuffTree::assignCodes(HuffNode *hn, std::string s) {

    if (!hn->left && !hn->right) {
        hn->code = s;
    }
    
    // if HuffNode is not a leaf (ie. left and right are NULL)
    else {

        // Repeat the process at both the left and right child
        if (hn->left) {
            assignCodes(hn->left, s + "0");
        } 
        if (hn->right) {
            assignCodes(hn->right, s + "1");
        }
    }
}

std::string HuffTree::getCodeHelper(HuffNode *hn, char c) {

    // POV: ur at a leaf node
    if (!hn->left && !hn->right) {

        // that leaf node is what you're looking for
        if (hn->data == c) {
            return hn->code;

        // it is not
        } else {
            return "";
        }

    } else {

        std::string l = getCodeHelper(hn->left, c);
        std::string r = getCodeHelper(hn->right, c);

        if (l.length() != 0) {
            return l;
        } else if (r.length() != 0) {
            return r;
        } else {
            return "";
        }
    }    
}

// https://www.techiedelight.com/delete-given-binary-tree-iterative-recursive/
void HuffTree::deleteTree(HuffNode *hn) {

    // Base case: empty tree
    if (hn == nullptr) {
        return;
    }
 
    // delete left and right subtree first (Postorder)
    deleteTree(hn->left);
    deleteTree(hn->right);
 
    // delete the current node after deleting its left and right subtree
    delete hn;
 
    // set root as null before returning
    hn = nullptr;
}