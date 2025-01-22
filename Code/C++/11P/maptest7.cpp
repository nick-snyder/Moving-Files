// tests cases for map::insert() method and iterator

#include "map.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

int main(){
	Map<int, int> m1;
	Map<int, int>::Iterator it;

	for(int i=1; i<=10000000; i++)
		m1.insert(i,0);
    	
	it = m1.begin();
	int key = 1; 
	while(it != m1.end()){
		assert(it->key == key);
		it++;
		key++;
	}
}




