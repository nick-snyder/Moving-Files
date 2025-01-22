// Program to shortest path from a given source vertex ‘s’ to
// a given destination vertex ‘t’. Expected time complexity
// is O(V+E).
#include<bits/stdc++.h>
using namespace std;

// This class represents a directed graph using adjacency
// list representation
class Graph
{
	int V; // No. of vertices
	list<char> *adj; // adjacency lists
public:
	Graph(int V); // Constructor
	void addEdge(char v, char w, int weight); // adds an edge

	// finds shortest path from source vertex ‘s’ to
	// destination vertex ‘d’.
	int findShortestPath(char s, char d);

	// print shortest path from a source vertex ‘s’ to
	// destination vertex ‘d’.
	int printShortestPath(char parent[], char s, char d);
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<char>[2*V];
}

void Graph::addEdge(char v, char w, int weight)
{
	// split all edges of weight 2 into two
	// edges of weight 1 each. The intermediate
	// vertex number is maximum vertex number + 1,
	// that is V.
	if (weight==2)
	{
		adj[v].push_back(v+V);
		adj[v+V].push_back(w);
	}
	else // Weight is 1
		adj[v].push_back(w); // Add w to v’s list.
}

// To print the shortest path stored in parent[]
int Graph::printShortestPath(char parent[], char s, char d)
{
	static int level = 0;

	// If we reached root of shortest path tree
	if (parent[s] == -1)
	{
		cout << "Shortest Path between " << s << " and "
			<< d << " is " << s << " ";
		return level;
	}

	printShortestPath(parent, parent[s], d);

	level++;
	if (s < V)
		cout << s << " ";

	return level;
}

// This function mainly does BFS and prints the
// shortest path from src to dest. It is assumed
// that weight of every edge is 1
int Graph::findShortestPath(char src, char dest)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[2*V];
	char *parent = new char[2*V];

	// Initialize parent[] and visited[]
	for (int i = 0; i < 2*V; i++)
	{
		visited[i] = false;
		parent[i] = -1;
	}

	// Create a queue for BFS
	list<char> queue;

	// Mark the current node as visited and enqueue it
	visited[src] = true;
	queue.push_back(src);

	// 'i' will be used to get all adjacent vertices of a vertex
	list<char>::iterator i;

	while (!queue.empty())
	{
		// Dequeue a vertex from queue and print it
		char s = queue.front();

		if (s == dest)
			return printShortestPath(parent, s, dest);

		queue.pop_front();

		// Get all adjacent vertices of the dequeued vertex s
		// If a adjacent has not been visited, then mark it
		// visited and enqueue it
		for (i = adj[s].begin(); i != adj[s].end(); ++i)
		{
			if (!visited[*i])
			{
				visited[*i] = true;
				queue.push_back(*i);
				parent[*i] = s;
			}
		}
	}
}

// Driver program to test methods of graph class
int main()
{
	// Create a graph given in the above diagram
	int V = 6;
	Graph g(V);
	g.addEdge('A', 'B', 2);
	g.addEdge('A', 'C', 3);
	g.addEdge('B', 'C', 1);
	g.addEdge('B', 'D', 1);
	g.addEdge('B', 'E', 4);
	g.addEdge('C', 'F', 5);
	g.addEdge('D', 'E', 1);
    g.addEdge('E', 'F', 1);
    g.addEdge('G', 'F', 1);

	char src = 'A'; 
    char dest = 'B';
	cout << "\nShortest Distance between " << src
		<< " and " << dest << " is "
		<< g.findShortestPath(src, dest);

	return 0;
}
