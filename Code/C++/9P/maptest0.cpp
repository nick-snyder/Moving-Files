#include "map.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{    
    Map<string, string> m1;

    cout << "\n\nMap test 1\n\n";

    assert(m1.find("dead") == m1.end());
    cout << "dead has not been found\n";

    assert( m1.insert("bad", "boy") == true);
	cout << m1 << endl;
	cout << "+++++++++++++++++++++++++++++" << endl;

	assert( m1.insert("cool", "breeze") == true);
	cout << m1 << endl;
	cout << "+++++++++++++++++++++++++++++"<< endl;
	
	assert( m1.insert("red", "rose") == true);
	cout << m1 << endl;
	cout << "+++++++++++++++++++++++++++++"<< endl;

	assert( m1.insert("warm", "fire") == true);
	cout << m1 << endl;
	cout << "+++++++++++++++++++++++++++++"<< endl;

    assert( m1.insert("dead", "person") == true);
	cout << m1 << endl;
	cout << "+++++++++++++++++++++++++++++"<< endl;

	assert( m1.insert("warm", "car") == false);

    Map<string, string>::Iterator it = m1.find("dead");
    assert(it != m1.end());
    cout << "dead has been found to have data: " << (*it).data << "\n";\

    // erase value in tree
    assert( m1.erase("red") == true);
    cout << m1 << endl;
	cout << "+++++++++++++++++++++++++++++"<< endl;

    // erase value not in tree
    assert( m1.erase("pizza") == false);

    Map<string, string>::Iterator iter = m1.begin();
    while (iter != m1.end()) 
    {
        cout << iter->key << " ";
        iter++;
    }
    
    iter++;
    iter++; 
    
    cout << "\n\nMap test 2\n\n";

    Map<int, int> m2;

    m2[29] = 1;
    m2[34] = 1;
    m2[39] = 1;
    m2[23] = 1;
    m2[87] = 1;
    m2[45] = 1;
    m2[83] = 1;
    m2[22] = 1;
    m2[12] = 1;
    m2[57] = 1;
    m2[21] = 1;
    m2[30] = 1;
    m2[2] = 1;
    m2[26] = 1;
    m2[5] = 1;
    m2[11] = 1;
    m2[32] = 1;
    m2[86] = 1;

    cout << m2 << "\n\n\n\n\n";
    
    m2[29] = 2;
    m2[34] = 2;
    m2[39] = 2;
    m2[23] = 2;
    m2[87] = 2;
    m2[45] = 2;
    m2[83] = 2;
    m2[22] = 2;
    m2[12] = 2;
    m2[57] = 2;
    m2[21] = 2;
    m2[30] = 2;
    m2[2] = 2;
    m2[26] = 2;
    m2[5] = 2;
    m2[11] = 2;
    m2[32] = 2;
    m2[86] = 2;

    cout << m2 << "\n\n";
    
    Map<int, int>::Iterator iter2 = m2.begin();
    while (iter2 != m2.end())
    {
        cout << iter2->key << " ";
        iter2++;
    }

	cout << endl;
}
