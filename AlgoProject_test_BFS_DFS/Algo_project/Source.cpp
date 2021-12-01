// A simple representation of graph using STL
#include<iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include <cstdlib>
#include <random>
#include <chrono>
#include <math.h> 
#include<fstream>
#include <time.h> 
#include "Graph.h"

using namespace std;



int bfs(Graph& g, int src, int& connect)
{
	int ver = g.sum_of_vert();
	list<int> queue;
	int * dist = new int[ver]{INT_MAX};
	bool *visited = new bool[ver] {false};
	visited[src] = true;
	int max = 0;
	
	dist[src] = 0;
	queue.push_back(src);
	int counter = 0;
	while (!queue.empty()) {
		src = queue.front();
		queue.pop_front();
			for(auto & cur : g.neighbors(src))
			{
				if (visited[cur] == false) {
					visited[cur] = true;
					dist[cur] = dist[src] + 1;
					queue.push_back(cur);
					counter++;
					if (dist[cur] > max) {
						max = dist[cur];
					}
				}
		    }
	}

	counter != ver - 1 ? connect = 0 : connect = 1;
	
	delete[] visited;
	delete[] dist;
	return max;
}


float Random(float MIN, float MAX) {
	return  MIN + (rand() / static_cast<float>(RAND_MAX / (MAX - MIN)));
}

Graph build_random_graph(int v, float p) {
	int i = 0, j = 0;
	Graph g(v);
	for (i = 0; i < v; i++)
	{
		for (j = 0; j < i; j++)
		{
			if (Random(0,1) <= p)
			{
				g.addEdge(i, j);
			}
		}
	}
	return g;
}

int is_isolated(Graph& g) {

	return g.is_isolated();

}

int connectivity(Graph& g) {
	int connected = 0;
	bfs(g, 0, connected);
	return connected;
}

int diameter(Graph& g) {
	int connected = 0;
	int diameter = 0;
	int max_diameter = 0;
	int num_of_vert = g.sum_of_vert();

	max_diameter = bfs(g, 0, connected);
	if (connected == 0) return INT_MAX;
	for (int i = 1; i < num_of_vert; i++)
	{
		diameter = bfs(g, i, connected);
		if (diameter > max_diameter)
		{
			max_diameter = diameter;
		}
	}
	return max_diameter;
}



void buildTheArray(float *array, float threshold )
{
	int j;
	for (j = 1; j <= 10; j++)
	{
		j < 6 ? array[j - 1] = Random(0, threshold):
			array[j - 1] = Random(threshold, (threshold + threshold * 0.001));
	}
	sort(array, array + 10);
}


float testIsolated( int v, float p, int runs){
	float sum =0;
	for (int j = 0; j < runs; j++)
	{
		Graph g = build_random_graph(v, p);
		sum +=is_isolated(g);
	}
	return sum / float(runs);
}

float testConnective(int v, float p, int runs){
	float sum =0;
	for (int j = 0; j < runs; j++)
	{
		Graph g = build_random_graph(v, p);
		sum +=connectivity(g);
	}
	return sum / float(runs);
	
}

float testDiameter(int v,float p,int runs){
	float sum =0;
	for (int i = 0; i < runs; i++)
	{
		Graph g = build_random_graph(v, p);
		sum +=diameter(g)<=2 ;
		cout<<"finished run: "<<i<<" in testDiameter out of "<<runs<<" tests."<<endl;
	}
	return sum / float(runs);
}


void createCSVTest(const char* filename,float(*fn)(int v,float p,int runs), int v,int runs, int probsCount, float* probs){
	ofstream file;
	file.open(filename);
	for(int i=0;i<probsCount-1;i++)
		file<<probs[i]<<","; //p0,p1,p2,...,p8,
	file<<probs[probsCount-1]<<"\n"; //<<p9\n
	for(int i=0;i<probsCount-1;i++){
		file<<fn(v,probs[i],runs)<<",";
		std::cout<<"Finished testing probability "<<i+1<<" of "<<probsCount<<std::endl;
	}
	file<< fn(v,probs[probsCount-1],runs)<<"\n";
	std::cout << "Finished testing probability " << 10 << " of " << probsCount << std::endl;
	file.close();
}


int main()
{
	srand(time(NULL));
	int v = 0;
	float num_of_grps = 0;
	int num_of_probs=10;
	cout << "please enter the num of graphs" << endl;
	cin >> num_of_grps;
	cout << "please enter the num of vertex" << endl;
	cin >> v;
	float threshold1_3 = (log(v) / v);
	float threshold2 = sqrt(2 * log(v) / v);
	float attr1[10];
	float attr2[10];
	float attr3[10];
	
	buildTheArray(attr1, threshold1_3);
	buildTheArray(attr2, threshold2);
	buildTheArray(attr3, threshold1_3);

	createCSVTest("attribute-1.csv",testConnective,v,num_of_grps,num_of_probs,attr1);
	createCSVTest("attribute-2.csv",testDiameter,v,num_of_grps,num_of_probs,attr2);
	createCSVTest("attribute-3.csv",testIsolated,v,num_of_grps,num_of_probs,attr3);


	return 0;
};
