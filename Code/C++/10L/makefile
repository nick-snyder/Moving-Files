CXX=g++

all: connectChecker DStest

connectChecker: connectChecker.cpp 
	clear
	$(CXX) -DDEBUG_PRINT  connectChecker.cpp -o connectChecker
	./connectChecker < data0

DStest: DisjointSet.h  DStest.cpp
	$(CXX)  DStest.cpp -o DStest

clean:
	rm -f *.o connectChecker DStest
