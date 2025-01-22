CXX=g++ 

all: set.o settest0 detective

set.o: set.cpp set.h
	clear
	$(CXX) -c set.cpp

settest0: set.o settest0.cpp
	clear
	$(CXX) settest0.cpp set.o -o settest0

detective: mysterysorts.o detective.cpp
	clear
	$(CXX) detective.cpp mysterysorts.o -o detective 

clean:
	rm -f set.o
	rm -f settest0
	rm -f detective
