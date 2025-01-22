CXX=g++

all: set.o setTest

set.o: set.cpp  set.h
	clear
	$(CXX) -c set.cpp

setTest: setTest.cpp  set.o set.h
	$(CXX) setTest.cpp set.o -lgtest -lpthread -o setTest

clean:
	rm -f *.o  setTest 
