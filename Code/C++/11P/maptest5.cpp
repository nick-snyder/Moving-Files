// tests for map::insert() and AVL tree structure 

#include "map.h"
#include <cassert>
#include <limits>
#include <cstddef>
#include <iostream>
using namespace std;


int main(){
	Map<int, int> m1;
	m1.insert(45,1);
	cout << "----------insert 45---------" << endl << m1;

	m1.insert(21,1);
	cout << "----------insert 21---------" << endl<< m1;

	m1.insert(4,1);
	cout << "----------insert 4---------" << endl<< m1;

	m1.insert(61,1);
	cout << "----------insert 61---------" << endl<< m1;

	m1.insert(71,1);
	cout << "----------insert 71---------" << endl<< m1;

	m1.insert(46,1);
	cout << "----------insert 46---------" << endl<< m1;

	m1.insert(2,1);
	cout << "----------insert 2---------" << endl<< m1;

	m1.insert(35,1);
	cout << "----------insert 35---------" << endl<< m1;

	m1.insert(36,1);
	cout << "----------insert 36---------" << endl<< m1;

	m1.insert(3,1);
	cout << "----------insert 3---------" << endl<< m1;

	m1.insert(8,1);
	cout << "----------insert 8---------" << endl<< m1;

	m1.insert(31,1);
	cout << "----------insert 31---------" << endl<< m1;

	m1.insert(12,1);
	cout << "----------insert 12---------" << endl<< m1;

	m1.insert(44,2);
	cout << "----------insert 44---------" << endl<< m1;

	m1.insert(30,2);
	cout << "----------insert 30---------" << endl<< m1;

	m1.insert(16,2);
	cout << "----------insert 16---------" << endl<< m1;

}
