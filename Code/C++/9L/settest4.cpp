#include <iostream>
#include <cstdlib>
#include <cassert>
#include "set.h"
using namespace std;

int main(){
	Set<int> s1;
	
	for (int i=1; i<128; i++){
		s1.insert(i);
	}
	cout << s1;
}
