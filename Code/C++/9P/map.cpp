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
		
	//Iterator it = find(key);
	return (find(key))->data;
}

// insert an element into the Map; return true if successful
template <typename KEY, typename T>
bool Map<KEY, T>::insert(KEY key, T data) {
	return insert(_root->left, key, data, _root);
}

// remove an element from the Map; return true if successful
template <typename KEY, typename T>
bool Map<KEY, T>::erase(KEY key) {

	// try to find key in tree. Iterator is not dereferenced later
	if (find(key) != end()) 
	{
		// assign e(cur) and p(parent)
		Elem *p = _root;
		Elem *e = _root->left;

		// traverse down the tree by first setting p to e and then setting e to the next node
		while (e) 
		{
			if (key < e->key) 
			{
				p = e;
				e = e->left;
			} 
			else if (key > e->key) 
			{
				p = e;
				e = e->right;
			} 
			else 
			{
				break;
			}
		}

		// if leaf node
		if (!e->left && e->rightThread) 
		{
			// if node is a left child of its parent
			if (p->left == e) 
			{
				p->left = nullptr;
			} 

			// else node is a right child of its parent
			else 
			{
				p->right = e->right;
				p->rightThread = true;
			}

			// decrement size and return true because key was found and deleted
			delete e;
			_size--;
			return true;
		} 

		// if node has only a right child
		else if (!e->left && !e->rightThread) 
		{
			// if node is a left child of its parent
			if (p->left == e) 
			{
				p->left = e->right;
			} 

			// else node is a right child of its parent
			else 
			{
				p->right = e->right;
			}

			// decrement size and return true because key was found and deleted
			delete e;
			_size--;
			return true;
		} 

		// if node has only a left child
		else if (e->left && e->rightThread) 
		{
			// if node is a left child of its parent
			if (p->left == e) 
			{
				p->left = e->left;
			} 

			// else node is a right child of its parent
			else 
			{
				p->right = e->left;
			}

			// traverse to in order predecessor of e
			Elem *predecessor = e->left;
			while (!predecessor->rightThread) 
			{
				predecessor = predecessor->right;
			}

			predecessor->right = e->right;
			
			// decrement size and return true because key was found and deleted
			delete e;
			_size--;
			return true;
		} 

		// else node has two children
		else 
		{
			// find in-order successor
			Elem *successor = e->right;
			Elem *successorP = e;
			while (successor->left) 
			{
				successorP = successor;
				successor = successor->left;
			}

			// swap e and its in order successor
			Elem *temp = e;
			e->key = successor->key;
			e->data = successor->data;
			successor->key = temp->key;
			successor->data = temp->data;
			
			// Remove Y from original location (using same algorithm)
			// pasted from above
			p = successorP;

			// if leaf node
			if (!successor->left && successor->rightThread) 
			{
				// if node is a left child of its parent
				if (p->left == successor) 
				{
					p->left = nullptr;
				} 

				// else node is a right child of its parent
				else 
				{
					p->right = successor->right;
					p->rightThread = true;
				}

				// decrement size and return true because key was found and deleted
				delete successor;
				_size--;
				return true;
			} 

			// if node has only a right child
			else if (!successor->left && !successor->rightThread) 
			{
				// if node is a left child of its parent
				if (p->left == successor) 
				{
					p->left = successor->right;
				} 

				// else node is a right child of its parent
				else 
				{
					p->right = successor->right;
				}

				// decrement size and return true because key was found and deleted
				delete successor;
				_size--;
				return true;
			} 

			// if node has only a left child
			else if (successor->left && successor->rightThread) 
			{
				// if node is a left child of its parent
				if (p->left == successor) 
				{
					p->left = successor->left;
				} 

				// else node is a right child of its parent
				else 
				{
					p->right = successor->left;
				}

				// traverse to in order predecessor of e
				Elem *predecessor = successor->left;
				while (!predecessor->rightThread) 
				{
					predecessor = predecessor->right;
				}

				predecessor->right = successor->right;
				
				// decrement size and return true because key was found and deleted
				delete successor;
				_size--;
				return true;
			} 
		}
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
void Map<KEY, T>::destructCode(Elem *& p) {

	// if (p->left == _root) 
	// {
	// 	delete p;
	// 	return;
	// }

	// if (p->left)
	// {
    // 	destructCode(p->left);
	// }

    // if (!p->rightThread)
	// {
    //     destructCode(p->right);
	// }

    // delete p;
	// _size--;

	if (_root->left == _root)
	{
		delete p;
	}

	if (p)
	{
		destructCode(p->left);

		if (!p->rightThread)
		{
			destructCode(p->right);
		}

		delete p;
	}
}

// helper method for inserting record into tree.
template <typename KEY, typename T>
bool Map<KEY, T>::insert(Elem *& root, const KEY &key, const T &data, Elem *lastLeft) {

	// tree is empty
	if (root == _root || root == 0) {
        root = new Elem;
        root->key = key;
		root->data = data;
        root->left = 0;
        root->right = lastLeft;
        root->rightThread = true;
		_size++;
        return true;
    }
    
    if (key == root->key) {
        return false;
    }

    // insert at left child
    if (key < root->key)
        return insert(root->left, key, data, root);
    
    // insert at right child
    if (!root->rightThread) {
        return insert(root->right, key, data, lastLeft);
    } 
	
	// insert at right thread
	else {  
        root->rightThread = false;
        root->right = new Elem;
        root->right->key = key;
		root->right->data = data; 
        root->right->left = 0;
        root->right->right = lastLeft;
        root->right->rightThread = true;
		_size++;
        return true;
    }
}

// output the structure of tree. The tree is output as "lying down"
// in which _root is the LEFT most Elem.
template <typename KEY, typename T>
void Map<KEY, T>::printTree(ostream& out, int level, Elem *p) const{
	int i;
	if (p) {
		if (p->right && !p->rightThread)
			printTree(out, level+1,p->right);
		for(i=0;i<level;i++) {
			out << "\t";
		}
		out << p->key << " " << p->data << '\n';
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
	return *_cur;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Elem* Map<KEY, T>::Iterator::operator->(){ 
	return _cur;
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::Iterator::operator++(int){

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
typename Map<KEY, T>::Iterator Map<KEY, T>::begin() const {

	if (size() == 0) 
	{
		return Iterator(_root);
	}

	Elem *e = _root->left;
	while (e->left) 
	{
		e = e->left;
	}
	return Iterator(e);
}

template <typename KEY, typename T>
typename Map<KEY, T>::Iterator Map<KEY, T>::end() const {
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
