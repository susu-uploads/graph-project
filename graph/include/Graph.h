//
// Created by mick on 12.02.2024.
//

#ifndef GRAPH_PROJECT_GRAPH_H
#define GRAPH_PROJECT_GRAPH_H


#include <string>
#include <vector>
#include "Edge.h"
#include "GraphAsEdgesList.h"
#include "GraphAsAdjList.h"
#include "GraphAsAdjMatrix.h"

class Graph {
private:
    int representation;
    GraphAsAdjMatrix graphAsAdjMatrix;
    GraphAsAdjList graphAsAdjList;
    GraphAsEdgesList graphAsEdgesList;
public:
    void readGraph(const std::string &n);

    void addEdge(int from, int to, int weight);

    void removeEdge(int from, int to);

    int changeEdge(int from, int to, int newWeight);

    void transformToAdjList();

    void transformToAdjMatrix();

    void transformToListOfEdges();

    void writeGraph(const std::string &fileName);
};


#endif //GRAPH_PROJECT_GRAPH_H
