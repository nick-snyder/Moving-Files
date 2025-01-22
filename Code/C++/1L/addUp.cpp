#include <iostream>
using namespace std;

int main(){
	int sum = 0;
	int value; 
	for (int i=0; i<100; i++){
		cin >> value;   // read from stdin
		sum += value;
	}
	
    cout << "Total is " << sum << endl;  // output to stdout
}

