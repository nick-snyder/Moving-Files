CXX=g++

all: addUp results.txt

addUp: addUp.cpp
	$(CXX)  addUp.cpp -o addUp
	
results.txt:
	./addUp < myNumbers > results.txt

clean:
	rm -f *.o addUp
	rm -f results.txt
