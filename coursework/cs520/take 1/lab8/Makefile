CXX = gcc
CFLAGS = -g -Wall -std=c99 -pthread

all: lab8-simple lab8-mutex lab8-cv

lab8-simple: lab8-simple.c
	$(CXX) $(CFLAGS) lab8-simple.c -o lab8-simple

lab8-mutex: lab8-mutex.c
	$(CXX) $(CFLAGS) lab8-mutex.c -o lab8-mutex

lab8-cv: lab8-cv.c
	$(CXX) $(CFLAGS) lab8-cv.c -o lab8-cv

clean:
	rm -f *.o lab8-simple lab8-mutex lab8-cv