//
// Created by mick on 12.02.2024.
//

#ifndef GRAPH_PROJECT_GRAPH_H
#define GRAPH_PROJECT_GRAPH_H


#include <string>
#include <vector>
#include "Edge.h"

class Graph {
private:
    std::vector<std::vector<Edge>> adjustmentList;
    std::vector<Edge> edgesList;
    std::vector<std::vector<int>> adjustmentMatrix;
    int representationType;
public:
    void readGraph(const std::string &fileName);

    void addEdge(int from, int to, int weight);

    void removeEdge(int from, int to);

    int changeEdge(int from, int to, int newWeight);

    void transformToAdjList();

    void transformToAdjMatrix();

    void transformToListOfEdges();

    void writeGraph(const std::string &fileName);
};


#endif //GRAPH_PROJECT_GRAPH_H
