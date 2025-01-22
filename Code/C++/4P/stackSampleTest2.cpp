/* This test driver tests stack interface methods using C asserts */

#include "stack.h"
#include <cassert>

int main(){
    stack s;

    assert(s.size()==0);
    assert(s.capacity()==8);
    assert(s.empty()==true);

    try {
        s.pop();
    } catch ( EmptyStackException e ) {
        cout << "exception caught \n";
    }

    assert(s.size()==0);
    assert(s.capacity()==8);
    assert(s.empty()==true);

    s.push(2);
    s.push(4);
    s.push(6);
    s.push(8);
    s.push(10);
    s.push(12);

    //std::cout << s.size() << std::endl;
    assert(s.size()==6);
    assert(s.capacity()==8);
    assert(s.empty()==false);

    s.push(14);
    s.push(16);
    //s.dump(std::cout);
    s.push(100);

    assert(s.size()==9);
    //std::cout << "Capacity: " << s.capacity() << std::endl;
    assert(s.capacity()==16);

    assert(s.top()==100);
    s.pop();
    assert(s.top()==16);
    s.pop();
    assert(s.top()==14);
    s.pop();
    assert(s.size()==6);
    assert(s.capacity()==16);
    s.dump(std::cout);

    // testing copy constructor
    stack t(s);
    assert(t.size()==s.size());
    s.pop();
    s.dump(std::cout);
    assert(t.top()==12);
    assert(s.top()==10);
    s.dump(std::cout);

    s.pop();
    s.pop();

    // testing assignment operator
    t = s;
    s.dump(std::cout);
    t.dump(std::cout);
    std::cout << "s Top: " << s.top() << std::endl; // 0
    std::cout << "t Top: " << t.top() << std::endl; // 0
    assert(t.top()==6);   // Why is t.top() == 6 ??

    try {
        s.pop();
        s.pop();
        s.pop();
        s.pop();
        s.pop();
        s.pop();
    } catch  ( EmptyStackException e ){
        cout << "exception caught \n";
    }
}
