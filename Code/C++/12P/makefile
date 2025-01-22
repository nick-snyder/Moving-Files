CC = g++
DEBUG = -g
EXECUTABLE = mynetwork
SOURCES = mynetwork.cpp DisjointSet.h PQueue.h


all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	clear
	$(CC) $(DEBUG) $< -o $@ 

	
clean:
	rm -f $(EXECUTABLE)
	