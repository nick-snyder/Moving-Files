CXX=g++

all: evaluation

evaluation: evaluation.cpp generateRPN.o
	clear
	$(CXX) -g evaluation.cpp generateRPN.o -o evaluation

clean: 
	rm -f evaluation
