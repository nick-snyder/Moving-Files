CXX=g++

skiptest0: skiplist.o skiptest0.o
	$(CXX) -g skiplist.o skiptest0.o -o skiptest0

skiplist.o: skiplist.cpp skiplist.h
	$(CXX) -c -g skiplist.cpp

skiptest0.o: skiptest0.cpp skiplist.h
	$(CXX) -c -g skiptest0.cpp
clean:
	rm -f *.o skiptest
