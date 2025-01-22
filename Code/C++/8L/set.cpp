/*
*/

#include "set.h"

Set::Set() 
: _size(0), _root(new TrieNode)
{
}

// insert a key into the set
// return false if key already exists; otherwise insert new key and return true
bool Set::insert(string key) {

    // if key is already in trie
    if (find(key))
        return false;
    
    // insert each letter of key (if not already there)
    TrieNode *tn = _root;
    for (int i = 0; i < key.length(); i++)
        if (find(to_string(key[i])))
            tn = tn->child[i - 'a'];    // 'a' == 97

    // add to trie
    tn->isWord = true;
    return true;
}

// remove a key from the set
// return false if the key doesn't exist; otherwise remove key and return true
bool Set::erase(string key) {

    // if key is not found in trie
    if (!find(key))
        return false;

    // go to end of key
    // check if TrieNode has children
        // if so... just set isWord to false and return true
        // if not... delete all TreeNodes up to next isWord == true or until _root

    // delete and/or set isWord to false
    return false;
}

// search for a key
// return true if an element is found; false otherwise
bool Set::find(string key) {
    // if (size() == 0)
    //     return false;

    // check if isWord is false?
    // check if whole key is in trie?
    TrieNode *tn = _root;
    
    for (int i = 0; i < key.length(); i++) {

        // if the current letter in the key is found in the 
        // child[] of the trie
        std::cout << "HERE\n";
        std::cout << "key: " << key[i] << " \n";
        std::cout << "in trie: " << tn->child[100 - 'a'] << " \n";

        if (true)//key[i] == *tn->child[i - 'a'])
            tn = tn->child[i - 'a'];    // move tn to next level
        else 
            return false;   // letter not found, return false
    }
    return true;
}

int Set::size() {
    return _size;
}