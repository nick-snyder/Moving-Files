#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>
#include <list>
#include <set>
#include <map>
#include "PQueue.h"
#include "DisjointSet.h"

struct Edge {
    char start, end;
    int weight;
    Edge(char a, char b, int c) : start(a), end(b), weight(c) {}
    bool operator<(Edge rhs) { return (this->weight < rhs.weight); }
    bool operator>(Edge rhs) { return (this->weight > rhs.weight); }
    std::ostream& operator<<(std::ostream& os) 
    {
        os << start << " <-> " << end << ":" << weight;
        return os;
    }
};

list<Edge> kruskalsAlgorithm(std::ifstream &file)
{
    PQueue<Edge*, 99> edges;
    list<Edge> listOfEdges;

    // 1. ds is already a forest of singletons
    DisjointSet<char> ds;

    std::string input;

    char node1;
    char node2;
    int weight;

    while (getline(file, input))
    {
        std::stringstream ss(input);

        ss >> node1;
        ss >> node2;
        ss >> weight;

        if (ss.fail())
        {
            break;
        }

        // debugging
        //std::cout << "EDGE: " << node1 << "--" << node2 << "\tWEIGHT: " << weight << std::endl;

        ds.createSet(node1);
        ds.createSet(node2);

        // 2. insert all edges into minimum priority queue
        Edge *e = new Edge(node1, node2, weight);
        edges.insert(e);
    }

    // debugging
    //edges.to_string();

    // 3. repeat until one tree remains
    while (!edges.isEmpty())
    {
        // 3.1. Remove least-cost edge from the priority queue
        Edge *e = edges.findMin();
        edges.deleteMin();

        // debugging
        //std::cout << "printing edge struct: " << e << std::endl;

        // 3.2. If the end vertices are in different sets (trees)
        if(ds.findSet(e->start) != ds.findSet(e->end))
        {
            // 3.2.1. Add the edge—it is “safe” because it won’t create a cycle
            listOfEdges.push_back(*e);

            // 3.2.2. Union the two vertices in the disjoint-set ADT
            ds.unionSets(e->start, e->end);
        }
    }
    return listOfEdges;
}

map<char, list<char> > constructGraph(list<Edge> listOfEdges)
{
    //construct map/graph
    map<char, list<char>> graph;
    for (list<Edge>::iterator it = listOfEdges.begin(); it != listOfEdges.end(); it++)
    {
        if (graph.find((*it).start) == graph.end())
        {
            graph[(*it).start].push_back((*it).end);
        }

        if (graph.find((*it).end) == graph.end())
        {
            graph[(*it).end].push_back((*it).start);
        }
    } 
    return graph;
}

queue<char> breadthFirstSearch(char start, char end, map<char, list<char>> graph)
{
    // 1. mark all vertices as unvisited
    set<char> visited;

    // 2. mark start_v as visited then queue.enqueue(start_v)
    visited.insert(start);
    queue<char> path;
    path.push(start);

    // 3. while !queue.empty() && queue.front() != end_v
    while (!path.empty() && path.front() != end)
    {
        // 3.1. v = queue.dequeue() 
        char v = path.front();
        path.pop();

        // 3.2  for each adjacent vertex a of v
        for (list<char>::iterator it = graph[v].begin(); it != graph[v].end(); it++)
        {
            // 3.2.1. if a not visited
            if (visited.find(*it) == visited.end())
            {
                // 3.2.1.1. mark a as visited
                visited.insert(*it);

                // 3.2.1.2 queue.enqueue(a)
                path.push(*it);
                //std::cout << "Enqueueing: " << *it << " to the path" << std::endl;
            }
        }
    }
    return path;
}

queue<char> findPath(char start, char end, std::ifstream &file)
{
    // debugging
    //std::cout << start << " " << end << std::endl;

    list<Edge> listOfEdges = kruskalsAlgorithm(file);

    map<char, list<char>> graph = constructGraph(listOfEdges);

    queue<char> path = breadthFirstSearch(start, end, graph);

    return path;
}

void printPath(queue<char> path)
{
    //std::cout << "path size: " << path.size() << std::endl;
    std::cout << "From: " << path.front() << std::endl;
        
    path.pop();

    //std::cout << "path size: " << path.size() << std::endl;

    while (!path.empty())
    {
        std::cout << "   To: " << path.front() << std::endl;
        path.pop();
    }
}

std::set<char> availableNodes(std::ifstream &file)
{
    std::set<char> possibleNodes;
    std::string input;

    char node;
    int weight;

    while (getline(file, input))
    {
        std::stringstream ss(input);

        ss >> node;
        possibleNodes.insert(node);

        ss >> node;
        possibleNodes.insert(node);

        ss >> weight;

        if (ss.fail())
        {
            break;
        }
    }
    return possibleNodes;
}

int main(int argc, char *argv[])
{
    // open file
    std::ifstream file1;
    file1.open(argv[1]);

    // copy of file
    std::ifstream file2;
    file2.open(argv[1]);

    // starting node
    char node = 'A';

    // possible nodes
    std::set<char> possibleNodes = availableNodes(file1);

    // stack of previous nodes
    stack<char> nodeHistory;

    // input
    std::string input;

    // minimum spanning tree
    queue<char> path;

    while (std::cin)
    {
        // show v node
        std::cout << "<" << node << "># ";

        // read input
        std::cin >> input;

        if (input == "ping")
        {
            // uses the MST to generate a stack of nodes that 
            // construct the path from the start node to the target node

            char start = node;
            char end;

            std::cin >> end;

            path = findPath(start, end, file2);
            printPath(path);
        }

        else if (input == "ssh")
        {
            // change the v node
            nodeHistory.push(node);

            std::cin >> node;

            while (possibleNodes.find(node) == possibleNodes.end())
            {
                // node not available
                std::cout << "Cannot find node.  Available nodes are:" << std::endl;

                // print available nodes
                std::set<char>::iterator it = possibleNodes.begin();
                while (it != possibleNodes.end())
                {
                    std::cout << "  " << *it << std::endl;
                    it++;
                }

                // read input
                std::cin >> node;
            }
        }

        else if (input == "exit")
        {
            // exits from the previous ssh
            if (nodeHistory.empty())
            {
                break;
            }
            else
            {
                node = nodeHistory.top();
                nodeHistory.pop();
            }
        }
    }
}
