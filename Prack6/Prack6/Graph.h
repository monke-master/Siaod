#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Edge {
	int src, dest, weight;

	bool operator < (const Edge& edge) {
		return weight < edge.weight;
	}
};


class Graph {
private:
	int vertexCount;
	int edgesCount;
	vector<Edge> edgesList;
	vector<vector<pair<int, int>>> adjList;
	void dfs(int vertex, int parent = -1);
public:
	void createGraph(int vertexCount, int edgesCount);
	void printGraph();
	void findBridges();
	vector<Edge> getSpanningTree();
	static void printTree(vector<Edge> edges);
};

