#include "Graph.h"



void Graph::createGraph(int n, int edgesCount) {
    vector<Edge> edges;
    Edge edge;
    int src, dest, weight;
    vertexCount = n;
    this->edgesCount = edgesCount;
    for (int i = 0; i < edgesCount; i++) {
        cin >> src;
        edge.src = src;
        cin >> dest;
        edge.dest = dest;
        cin >> weight;
        edge.weight = weight;
        edges.push_back(edge);
        edgesList.push_back(edge);

        edge.src = dest;
        edge.dest = src;
        edges.push_back(edge);
    }

    adjList.resize(n);

    for (auto& edge : edges)
    {
        int src = edge.src;
        int dest = edge.dest;
        int weight = edge.weight;
        adjList[src - 1].push_back(make_pair(dest, weight));
    }
}


void Graph::printGraph()
{
    for (int i = 0; i < adjList.size(); i++)
    {
        for (pair<int, int> v : adjList[i]) {
            cout << "(" << i + 1 << ", " << v.first << ", " << v.second << ") ";
        }
        cout << endl;
    }
}

vector<bool> used;
int timer = 0;
int* tin;
int* fup;


void Graph::dfs(int vertex, int parent)
{
    used[vertex - 1] = true;
    tin[vertex - 1] = fup[vertex - 1] = timer++;
    for (int i = 0; i < adjList[vertex - 1].size(); i++) {
        auto to = adjList[vertex - 1][i].first;
        if (to == parent) continue;
        if (used[to - 1])
            fup[vertex - 1] = min(fup[vertex - 1], tin[to - 1]);
        else {
            dfs(to, vertex);
            fup[vertex - 1] = min(fup[vertex - 1], fup[to - 1]);
            if (fup[to - 1] > tin[vertex - 1])
                cout << "Edge " << vertex << " - " << to << " is a bridge" << endl;
        }
    }
}

void Graph::findBridges() {
    tin = new int[vertexCount];
    fup = new int[vertexCount];
    for (int i = 0; i < vertexCount; i++)
        used.push_back(false);
    for (int i = 0; i < vertexCount; i++) {
        if (!used[i]) dfs(i + 1);
    }

}

vector<Edge> Graph::getSpanningTree()
{
    sort(
        edgesList.begin(),
        edgesList.end()
    );

    vector<int> treeId(vertexCount);
    for (int i = 0; i < vertexCount; i++)
        treeId[i] = i + 1;
    vector<Edge> result;
    int cost = 0;
    for (Edge edge : edgesList) {
        if (treeId[edge.src] != treeId[edge.dest]) {
            cost += edge.weight;
            result.push_back(edge);
            int oldId = treeId[edge.dest];
            int newId = treeId[edge.src];
            for (int j = 0; j < vertexCount; j++) {
                if (treeId[j] == oldId)
                    treeId[j] = newId;
            }
        }
    }
    return result;

}

void Graph::printTree(vector<Edge> edges)
{
    sort(
        edges.begin(),
        edges.end(),
        [](Edge a, Edge b) {
            if (a.src == b.src)
                return a.dest < b.dest;
            return a.src < b.src;
        }
    );

    for (Edge edge : edges) {
        cout << min(edge.src, edge.dest) << " --> " << max(edge.src, edge.dest) << " weight: " << edge.weight << endl;;
    }
}
