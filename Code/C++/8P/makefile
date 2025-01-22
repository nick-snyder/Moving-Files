CXX=g++

all: HuffTree.o HuffmanCoder testHuff1 testHuff2 testHuff3 testHuff4

HuffTree.o: PQueue.h PQueue.cpp HuffTree.cpp HuffTree.h
	clear
	$(CXX) -c HuffTree.cpp 

HuffmanCoder: HuffmanCoder.cpp HuffTree.o
	clear
	$(CXX) HuffmanCoder.cpp HuffTree.o -o HuffmanCoder


testHuff1: testHuff1.cpp HuffTree.o
	$(CXX) -g testHuff1.cpp HuffTree.o -o testHuff1

testHuff2:
	$(CXX) testHuff2.cpp HuffTree.o -o testHuff2

testHuff3:
	$(CXX) testHuff3.cpp HuffTree.o -o testHuff3

testHuff4: 
	$(CXX) testHuff4.cpp HuffTree.o -o testHuff4

clean:
	rm -f *.o HuffTree.o HuffmanCoder testHuff1 testHuff2 testHuff3 testHuff4
