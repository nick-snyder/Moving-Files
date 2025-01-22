CXX=g++
all: set.o settest0.o

set.o: set.cpp set.h
	clear
	$(CXX) -c set.cpp 

settest0.o: set.o settest0.cpp
	$(CXX) settest0.cpp set.o -o settest0

clean:
	rm -f set.o
	rm -f settest0.o