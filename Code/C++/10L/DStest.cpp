#include "DisjointSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main(){
    DisjointSet<int> s;
   
    /*
     *   you fill in here to set up the disjoint set 
     */
    s.unionSets(3, 5);
    s.unionSets(4, 2);
    s.unionSets(1, 6);
    s.unionSets(5, 7);
    s.unionSets(4, 8);
    s.unionSets(3, 7);
    s.unionSets(8, 1);
    
    assert(s.findSet(1) == s.findSet(6)); // 1 and 6 are connected.
    assert(s.findSet(3) != s.findSet(6)); // 3 and 6 are not connected.
    assert(s.findSet(1) == s.findSet(1)); // 1 and 1 are connected.
    assert(s.findSet(3) == s.findSet(5)); // 3 and 5 are connected.
    assert(s.findSet(3) != s.findSet(9)); // 3 and 9 are not connected.
    
}
