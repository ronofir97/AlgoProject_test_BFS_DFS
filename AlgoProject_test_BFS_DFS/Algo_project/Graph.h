#pragma once
#include <unordered_set>

class Graph {
public:
	Graph(int vertices);
	Graph(Graph && garph);
	void addEdge(int src, int dest);
	void print_adj_list();
	int is_isolated();
	int sum_of_vert();
	std::unordered_set<int> & neighbors(int v);
	~Graph();

private:
	int numVertices;
	//array of set
	std::unordered_set<int> *adjSet;
};
