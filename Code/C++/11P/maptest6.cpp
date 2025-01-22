// tests cases for map::insert() method

#include "map.h"
#include <cassert>
#include <limits>
#include <cstddef>
#include <iostream>
using namespace std;


int main(){
	Map<int,int> m1;
	m1.insert(40,1);
	m1.insert(12,1);
	m1.insert(6,1);
	m1.insert(78,1);
	m1.insert(45,1);
	m1.insert(33,1);
	m1.insert(21,1);
	m1.insert(4,1);
	m1.insert(29,1);
	m1.insert(9,1);
	m1.insert(5,1);
	m1.insert(42,1);
	m1.insert(23,1);
	m1.insert(11,1);
	m1.insert(64,1);
	m1.insert(46,1);
	m1.insert(20,1);
	m1.insert(13,1);
	m1.insert(28,1);
	m1.insert(54,1);
	m1.insert(77,1);
	m1.insert(85,1);
	m1.insert(14,1);
	m1.insert(17,1);
	m1.insert(15,1);
	m1.insert(9,1);
	m1.insert(56,1);
	m1.insert(47,1);
	m1.insert(83,1);
	m1.insert(31,1);
	m1.insert(59,1);
	m1.insert(66,1);
	m1.insert(61,1);
	m1.insert(63,1);
	m1.insert(23,1);
	m1.insert(69,1);
	m1.insert(70,1);
	m1.insert(89,1);
	m1.insert(91,1);
	m1.insert(67,1);
	m1.insert(75,1);

	assert(m1.size()==39);
	cout << m1;
}
