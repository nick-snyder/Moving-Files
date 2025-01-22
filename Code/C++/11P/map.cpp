// A generic Map implemented with right-threaded BST
// BST is not balanced

#include <map> // helper container for thread copying
#include <iostream>

template <typename KEY, typename T>
Map<KEY, T>::Map(){
	// create a dummy root node
	_root = new Elem;
	_root->left = _root;  // empty tree
	_root->right = 0;
	_root->rightThread = true;
	_size = 0;
}

// copy constructor 
template <typename KEY, typename T>
Map<KEY, T>::Map(const Map<KEY,T> &v){
	// if empty tree
	if (v._root == v._root->left){
		//_root = new Elem;
		_root->left = _root;  // empty tree
		_root->right = 0;
		_root->rightThread = true;
		_size = 0;
	} else {
		_root = new Elem;
		_root->left = _root;
		_root->right = 0;
		_root->rightThread = true;
		copyCode(_root->left, v._root->left); // to deep copy the tree without dummy nodes
		copyThread(_root, v._root); // to copy the threading; must pass dummy nodes to complete the threads
		_size = v._size;
	}
}

// destructor
template <typename KEY, typename T>
Map<KEY, T>::~Map() {
	destructCode(_root);
}

// assignment operator
template <typename KEY, typename T>
typename Map<KEY, T>::Map& Map<KEY, T>::operator=(const Map &rhs) {
	if (this != &rhs) {
		if (size() > 0)
		{
			destructCode(_root);

			_root = new Elem;
			_root->left = _root;
			_root->right = 0;
			_root->rightThread = true;
		}
        
        copyCode(_root->left, rhs._root->left);
		copyThread(_root, rhs._root); // to copy the threading; must pass dummy nodes to complete the threads
		_size = rhs._size;
    }
    return *this;
}

// overloaded subscript operator
template <typename KEY, typename T>
T& Map<KEY, T>::operator[](KEY key) {

	// if key is not found in tree
	if (find(key) == this->end()) {

		// insert the new key with no data
		T data;
		insert(key, data);
	}
		
	return (find(key))->data;
}

// insert an element into the Map; return true if successful
template <typename KEY, typename T>
bool Map<KEY, T>::insert(KEY key, T data) {

	if (find(key) == end()) 
	{
		insert(key, data, _root->left, _root);
		return true;
	}
	else
	{
		return false;
	}
}

// remove an element from the Map; return true if successful
template <typename KEY, typename T>
bool Map<KEY, T>::erase(KEY key) {

	//bool ret = false;

	// try to find key in tree. Iterator is not dereferenced later
	if (find(key) != end()) {

		bool done = false;

		// assign e(cur) and p(parent)
		Elem *p = _root;
		Elem *e = _root->left;
		Elem *successor = e;

		// traverse down the tree by first setting p to e and then setting e to the next node
		int i = 0;
		while (e) {
			std::cout << i << std::endl;
			if (key < e->key) {
				p = e;
				e = e->left;
			} else if (key > e->key) {
				p = e;
				e = e->right;
			} else {
				break;
			}
			i++;
		}

		while (!done) {

			e = successor;

			// if leaf node
			if (!e->left && e->rightThread) {

				std::cout << "Node: \"" << e->key << "\" has no children\n";

				if (p->left == e) {
					p->left = nullptr;
				} else {
					p->right = e->right;
					p->rightThread = true;
				}

				// decrement size and return true because key was found and deleted
				delete e;
				_size--;
				done = true;

			// if only right child
			} else if (!e->left && !e->rightThread) {

				std::cout << "Node: \"" << e->key << "\" has a right child\n";

				if (p->left == e) {
					p->left = e->right;
				} else {
					p->right = e->right;
				}

				// decrement size and return true because key was found and deleted
				delete e;
				_size--;
				done = true;

			// if only left child
			} else if (e->left && e->right == e) {

				std::cout << "Node: \"" << e->key << "\" has a left child\n";

				if (p->left == e) {
					p->left = e->left;
				} else {
					p->right = e->left;
				}

				// traverse to in order predesssor of e
				Elem *predessor = e->left;
				while (!predessor->rightThread) {
					predessor = e->right;
				}

				predessor->right = e->right;
				
				// decrement size and return true because key was found and deleted
				delete e;
				_size--;
				done = true;

			// else node has two children
			} else {

				std::cout << "Node: \"" << e->key << "\" has both children\n";
				
				// traverse to in order successor
				successor = e->right;
				while (successor->left) {
					successor = e->left;
				}

				// swap e and its in order successor
				Elem *temp = e;
				e->key = successor->key;
				e->data = successor->data;
				successor->key = temp->key;
				successor->data = temp->data;

				std::cout << "Recursing...\n";
				//return erase(key);
			}
		}
		return true;
	} 

	return false;
}

// return size of the Map
template <typename KEY, typename T>
int Map<KEY, T>::size() const{
	return _size;
}

// common copy code for deep copy a tree without copying threads
template <typename KEY, typename T>
void  Map<KEY,T>::copyCode(Elem* &newRoot, Elem* origRoot){
	if (origRoot == 0)
		newRoot = 0;
	else{
		newRoot = new Elem;
		newRoot->key = origRoot->key;
		newRoot->data = origRoot->data;
		newRoot->rightThread = origRoot->rightThread; 
		copyCode(newRoot->left, origRoot->left);
		if (!origRoot->rightThread) 
			copyCode(newRoot->right, origRoot->right);
	}
} 

// common code for deallocation
template <typename KEY, typename T>
void Map<KEY, T>::destructCode(Elem *& node) {

	if (_root->left == _root)
	{
		delete node;
	}

	if (node)
	{
		destructCode(node->left);

		if (!node->rightThread)
		{
			destructCode(node->right);
		}

		delete node;
	}
}

// from set.cpp
// helper method for recusive insertion
template<typename KEY, typename T>
void Map<KEY, T>::insert(const KEY &key, const T &data, Elem *& node, Elem *& parent) {

	/////////////////    Insert at leaf node/root    /////////////////

    if (node == 0)
	{
        node = new Elem;
		node->left = 0;
		node->right = parent->right;
		parent->right = node;
		parent->rightThread = false;
		node->rightThread = true;
		node->key = key;
		node->data = data;
		node->height = 0;
        _size++;
    }

	/////////////////    Recursively move to where node fits    /////////////////
	
    // move to left
    else if (key < node->key) 
	{
        insert(key, data, node->left, node);
    }
    // move to right
    else if (key > node->key) 
	{
		if (node->rightThread)
		{
			node = new Elem;
			node->left = 0;
			node->right = parent->right;
			parent->right = node;
			parent->rightThread = false;
			node->rightThread = true;
			node->key = key;
			node->data = data;
			node->height = 0;
			_size++;
		}
		else
		{	
			insert(key, data, node->right, node);
		}
        
    }

	/////////////////    Re-balance tree    /////////////////

	int loadFactor;
	if (node->rightThread) 
	{
		loadFactor = height(node->left) + 1;
	}
	else
	{
		loadFactor = height(node->left) - height(node->right);
	}

	// calculate load factor
	if (loadFactor == 2) 
	{ 
		// outside case
		if (key < node->left->key) 
		{
			rotateRight(node);
		}
		// inside case
		else 
		{
			doubleRotateRight(node);
		}
	}

	// calculate load factor
	if (loadFactor == -2) 
	{
		// outside case
		if (key > node->right->key) 
		{
			rotateLeft(node);
		}
		// inside case
		else  
		{
			doubleRotateLeft(node);
		}
	}

	/////////////////    update height of node    /////////////////

	int i = -1;
	if (node->rightThread)
	{
		i = 0;
	}
	else 
	{
		i = height(node->right);
	}
    node->height = max(height(node->left), i) + 1;
}

template <typename KEY, typename T>
int Map<KEY, T>::height(Elem *node) {
    return node == 0 ? -1 : node->height;
}

// single right rotation
template <typename KEY, typename T>
void Map<KEY, T>::rotateRight(Elem *& node) {
	
	/////////////////    rotate nodes    /////////////////

    Elem * beta = node->left;

	if (beta->rightThread)
	{
		node->left = NULL;
		node->rightThread = false;
	}
	else 
	{
		node->left = beta->right;
	}
    
    beta->right = node;
    node = beta;

	/////////////////    update height of nodes    /////////////////

	if (node->rightThread)
	{
		node->height = height(node->left) + 1;
	}
	else
	{
		node->height = max(height(node->left), height(node->right)) + 1;
	}

	if (node->right->rightThread)
	{
		node->right->height = height(node->right->right) + 1;
	}
	else
	{
		node->right->height = max(height(node->right->left), height(node->right->right)) + 1;
	}

	// int i;
	// if (node->rightThread)
	// {
	// 	int i = 0;
	// }
	// else 
	// {
	// 	i = height(node->right);
	// }
    // node->height = max(height(node->left), i) + 1;

	// int j;
	// if ( (!node->rightThread) && (node->right->rightThread) )
	// {
	// 	j = 0;
	// }
	// else if (!node->rightThread)
	// {
	// 	j = height(node->right->right);
	// }
    // node->right->height = max(height(node->right->left), i) + 1;

	/////////////////    update threads    /////////////////


}

// single left rotation
template <typename KEY, typename T>
void Map<KEY, T>::rotateLeft(Elem *& node){
    
	/////////////////    rotate nodes    /////////////////

    Elem * beta = node->right;
	if (beta->left)
	{
		node->right = beta->left;
	}
    else
	{
		node->rightThread = true;
	}
	beta->left = node;
    node = beta;

	/////////////////    update height of nodes    /////////////////

	if (node->rightThread)
	{
		node->height = height(node->left) + 1;
	}
	else 
	{
		node->height = max(height(node->left), height(node->right)) + 1;
	}

	if (node->rightThread)
	{
		node->left->height = height(node->left->left) + 1;
	}
	else
	{
		node->left->height = max(height(node->left->left), height(node->left->right)) + 1;
	}

	// int i;
	// if (node->rightThread)
	// {
	// 	i = 0;
	// }
	// else
	// {
	// 	i = height(node->right);
	// }
	// node->height = max(height(node->left), i) + 1; 

	// int j;
	// if (node->left->right->rightThread)
	// {
	// 	j = 0;
	// }
	// else if (!node->rightThread)
	// {
	// 	j = height(node->left->right);
	// }
    // node->left->height = max(height(node->left->left), j) + 1; 

	/////////////////    update threads    /////////////////


}

// double right rotation
template <typename KEY, typename T>
void Map<KEY, T>::doubleRotateRight(Elem *& node) {
    // you fill in here
    rotateLeft(node->left);
    rotateRight(node);
}

// double left rotation
template <typename KEY, typename T>
void Map<KEY, T>::doubleRotateLeft(Elem *& node) {
    // you fill in here
    rotateRight(node->right);
    rotateLeft(node);
}

// output the structure of tree. The tree is output as "lying down"
// output each node's key, value and its tree height 
template <typename KEY, typename T>
void Map<KEY, T>::printTree(ostream& out, int level, Elem *p) const{
	int i;
	if (p) {
		if (p->right && !p->rightThread)
			printTree(out, level+1,p->right);
		for(i=0;i<level;i++) {
			out << "\t";
		}
		out << p->key << " " << p->data << "(" << p->height << ")" << '\n';
		printTree(out, level+1,p->left);
	}
}

// construct a key-element map to rethread the new tree
// the map contains all nodes key values and their corresonding elem node address 
// for furture lookup in setting up threads
template <typename KEY, typename T>
void Map<KEY, T>::addToMap(Elem* root, map<KEY, Elem*> &keyElemMap){
	if (root) {
		keyElemMap[root->key] = root; 
		addToMap(root->left, keyElemMap);
		if (!root->rightThread)
			addToMap(root->right, keyElemMap);
	}
}

// common copy code for thread copying
template <typename KEY, typename T>
void Map<KEY, T>::copyThread(Elem* &newRoot, Elem* origRoot){
	// construct the key-element map for new and orig tree
	map<KEY, Elem*> newKeyElemMap; 
	map<KEY, Elem*> origKeyElemMap;
	addToMap(newRoot->left, newKeyElemMap);
	addToMap(origRoot->left, origKeyElemMap);

	// start at the last element in the tree, which threads to root
	typename std::map<KEY, Elem*>::reverse_iterator it = origKeyElemMap.rbegin();
	newKeyElemMap[it->first] -> rightThread = true;
	newKeyElemMap[it->first] -> right = newRoot;
	
	// then thread the rest of the tree backwardly 
	it++;
	while(it != origKeyElemMap.rend()){
		if (it->second->rightThread){
			newKeyElemMap[it->first] -> rightThread = true;
			newKeyElemMap[it->first] -> right = newKeyElemMap[ origKeyElemMap[it->first]->right->key ];
		}
		it++;
	} 
}

template <typename KEY, typename T>
typename Map<KEY, T>::Elem& Map<KEY, T>::Iterator::operator*(){ 
	// fill in here
	return *_cur;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Elem* Map<KEY, T>::Iterator::operator->(){ 
	// fill in here
	return _cur;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::Iterator::operator++(int){
	// fill in here

	if (_cur->rightThread) {
		_cur = _cur->right;
		return Iterator(_cur);
	} else {
		// traverse to in order successor
		if (_cur->right) {
			_cur = _cur->right;
		}
		while (_cur->left) {
			_cur = _cur->left;
		}
		return Iterator(_cur);
	}
}

template <typename KEY, typename T>
bool Map<KEY, T>::Iterator::operator==(Iterator it)  {
	return _cur == it._cur;
}

template <typename KEY, typename T>
bool Map<KEY, T>::Iterator::operator!=(Iterator it)  {
	return _cur != it._cur;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::begin() const {  // return the left most (smallest) tree node
	// fill in here
	Elem *e = _root;
	while (e->left) {
		e = e->left;
	}
	return Iterator(e);
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::end() const {  // return the dummy root node
	// fill in here
	return Iterator(_root);
} 

// return an iterator pointing to the end if the element is not found,
// otherwise, return an iterator to the element
template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::find(KEY key) const {

	if (_root->left == _root) {
		return end();
	}

	Elem *e = _root->left;
	while (e) {

		if (e->key == key) {
			return Iterator(e);
		}

		if (key < e->key) {
			if (!e->left) {
				return end();
			}
			e = e->left;
		} 
		
		else {
			if (e->rightThread) {
				return end();
			}
			e = e->right;
		}
	}
	return end();
}

// outputs information in tree in inorder traversal order
template <typename KEY, typename T>
ostream& Map<KEY, T>::dump(ostream& out) const{
	if ( _root == _root->left) {// tree empty
		return out;
	}
	printTree(out, 0, _root->left);   // print tree structure
	return out;
}

// outputs using overloaded << operator
template<typename KEY, typename T>
ostream& operator<< (ostream& out, const Map<KEY, T>& v){
	v.dump(out);
	return out;
}
