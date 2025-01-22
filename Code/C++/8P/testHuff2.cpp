#include "HuffTree.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main(){
    HuffTree h;
    char c[8] = {'a', 'e', 'i', 's', 't', ' ', '\n', '*'};
    int f[8] = {16, 2, 64, 128, 4, 32, 8, 3};
    h.buildTree(c,f,8);

    cout << h.getCode('a') << endl;
    cout << h.getCode('e') << endl;
    cout << h.getCode('i') << endl;
    cout << h.getCode('s') << endl;
    cout << h.getCode('t') << endl;
    cout << h.getCode(' ') << endl;
    cout << h.getCode('\n') << endl;
    cout << h.getCode('*') << endl;

}

