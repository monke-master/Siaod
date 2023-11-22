#include <iostream>
#include "Graph.h"


#define PRINT 0
#define FIND_BRIDGES 1
#define TREE  2
#define END  -1

int main()
{
    auto graph = Graph();
    cout << "Enter vertex cout: \n";
    int n;
    cin >> n;
    int edgesCount;
    cout << "Enter edges cout: \n";
    cin >> edgesCount;

    cout << "Enter edges: start, end, weight: \n";
    graph.createGraph(n, edgesCount);
    int command;
    cout << "Available commands: \n";
    cout << PRINT << " - print graph \n";
    cout << FIND_BRIDGES << " - print bridges \n";
    cout << TREE << " - get spanning tree \n";
    cout << END << " - end the programm \n";
    while (true)
    {
        cin >> command;
        switch (command)
        {
            case PRINT:
                graph.printGraph();
                break;
            case FIND_BRIDGES:
                graph.findBridges();
                break;
            case TREE:
                graph.printTree(graph.getSpanningTree());
                break;
            case END:
                return 0;
            default:
                break;
        }
    }    
}

