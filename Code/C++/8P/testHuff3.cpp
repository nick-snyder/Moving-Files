#include "HuffTree.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main(){
    HuffTree h;
    char c[11] = {'a', 'e', 'i', 's', 't', ' ', 'z', 'p', 'w', '\n', '*'};
    int f[11] = {6, 41, 5, 9, 42, 8, 10, 43, 211, 44, 7};
    h.buildTree(c,f,11);

    cout << h.getCode('a') << endl;
    cout << h.getCode('e') << endl;
    cout << h.getCode('i') << endl;
    cout << h.getCode('s') << endl;
    cout << h.getCode('t') << endl;
    cout << h.getCode(' ') << endl;
    cout << h.getCode('z') << endl;
    cout << h.getCode('p') << endl;
    cout << h.getCode('w') << endl;
    cout << h.getCode('\n') << endl;
    cout << h.getCode('*') << endl;

}

