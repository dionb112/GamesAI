// Program to print BFS traversal from a given 
// source vertex. BFS(int s) traverses vertices 
// reachable from s. 
#include<iostream> 
#include <list> 

using namespace std;

// This class represents a directed graph using 
// adjacency list representation 
class Graph
{
	int V; // No. of vertices 

	// Pointer to an array containing adjacency 
	// lists 
	list<int>* adj;
public:
	Graph(); // Constructor 
	void init(int V);
	// function to add an edge to graph 
	void addEdge(int v, int w);

	// prints BFS traversal from a given source s 
	list<int> BFS(int s);
};
