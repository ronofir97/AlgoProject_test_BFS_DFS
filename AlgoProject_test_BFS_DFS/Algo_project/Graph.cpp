#include "Graph.h"
#include <iostream>
Graph::Graph(int vertices) {
	this->numVertices = vertices;
	adjSet = new std::unordered_set<int>[vertices];
}

Graph::Graph(Graph && o) { // moove constructor 
	this->adjSet = o.adjSet;
	this->numVertices = o.numVertices;
	o.adjSet = NULL;
}

void Graph::addEdge(int src, int dest) {
	if (src == dest) return;
	adjSet[src].insert(dest);
	adjSet[dest].insert(src);
}

void Graph::print_adj_list() {
	for (int i = 0; i < numVertices; i++)
	{
		std::cout << "vrtex " << i + 1 << "->  ";
		for (int nbr : adjSet[i]) {
			std::cout << nbr + 1 << ", ";
		}
		std::cout << std::endl;
	}
}

int Graph::is_isolated() {
	for (int i = 0; i < numVertices; i++)
	{
		if (adjSet[i].empty()) return 1;
	}
	return 0;
}

int Graph::sum_of_vert() {
	return this->numVertices;
}

std::unordered_set<int> & Graph::neighbors(int v) {
	return adjSet[v];
}


Graph::~Graph() {
	if (adjSet != NULL)
		delete[] adjSet;
}
