#include "DisjointSet0.h"

/**
* Creates a singleton set from the parameter.
*/
void DisjointSet::createSet(int n) {
    parents[n] = n;
    depths[n] = 0;
}

/**
* Finds and returns the representative of the set which contains the
* parameter. Implements path compression.
*/
int DisjointSet::findSet(int p) {
    if (p != parents[p]) 
        parents[p] = findSet(parents[p]);
    return parents[p];
}

/**
* Combines the sets which contain the parameters. Return false if two 
* parameters are already in the same set; otherwise, union the two sets
* by depths and return true
*/
bool DisjointSet::unionSets(int p, int q) {
    int xid = findSet(p);
    int yid = findSet(q);
    if (xid == yid)
        return false;
    if (depths[xid] > depths[yid])
        parents[yid] = xid;
    else {
        parents[xid] = yid;
        if (depths[xid] == depths[yid])
            depths[xid]++;
    }
    return true;
}