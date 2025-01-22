#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <sstream>
#include <set>
#include <iterator>
using namespace std;

string breadthFirstSearch(map<char, list<char>> graph, char start, char end) {

    set<char> visited;

    // Create a queue for BFS
    list<char> path;

    char c = start;

    // Mark the current node as visited and enqueue it
    visited.insert(c);

    path.push_back(c);

    string ret = "";
    list<char>::iterator it;

    while (!path.empty()) {
        //cout << "in the while loop\n";

        // Dequeue a vertex from path and print it
        c = path.front();
        cout << c << " ";
        ret += c;
        path.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex c. If a adjacent has not been visited,
        // then mark it visited and enqueue it

        // for each vertex in the graph
        // 
        int i = 0;
        for (it = graph[i].begin(); it != graph[i].end(); ++it) {            

            // if the vertex has not been visited
            if (visited.find(*it) == visited.end()) {

                // make it visited
                visited.insert(*it);

                // push it onto the queue
                path.push_back(*it);
            }

            i++;
        }
    }
    return ret;
}

string printPath(list<char> path) {
    string pathString = "";
    while (!path.empty()) {
        pathString += path.front();
        path.pop_front();
    }
    return pathString;
}

void printGraph(map<char, list<char> > &graph) {
    map<char, list<char> >::iterator graph_it;
    list<char>::iterator it;

    for (graph_it = graph.begin();
         graph_it != graph.end(); graph_it++)
    {
        cout << (*graph_it).first << ": "; 
        for (it = (*graph_it).second.begin();
             it != (*graph_it).second.end(); it++)
            cout << *it << " ";
        cout << endl;
    }
}

int main() {
    
    // build the graph 
    map<char, list<char> > graph;
    char v1, v2, start, end;

    //Process graph input
    while((cin >> v1) && v1 != '?')
    {
        if (!(cin >> v2))
            break;
        //REPLACE WITH CODE TO STORE EDGE IN GRAPH
        graph[v1].push_back(v2);
    }

#ifdef DEBUG_PRINT
    // display stored graph if compiled with -DDEBUG_PRINT
    printGraph(graph);
#endif

    //Process queries
    while (cin >> start >> end)
    {
        //REPLACE WITH CODE TO STORE OR PROCESS QUERIES

        cin >> v1; //grab the next '?'
        if (v1 == '?') {

            string path = breadthFirstSearch(graph, start, end);

            cout << "\nfrom " << start << " to " << end;
            if (path.length() > 0) {
                cout << " : path found.\n" << path << endl;
            } else {
                cout << " : path not found.\n";
            }
        }
    }
}

