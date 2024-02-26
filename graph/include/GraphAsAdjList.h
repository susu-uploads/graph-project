//
// Created by mick on 2/26/24.
//

#ifndef GRAPH_PROJECT_GRAPHASADJLIST_H
#define GRAPH_PROJECT_GRAPHASADJLIST_H


#include <vector>
#include <fstream>
#include "Edge.h"
#include "Node.h"

class GraphAsAdjList {
protected:
    std::vector<Node> adjustmentList;
    int size;
    int weighted;
    int directed;
public:
    void addEdge(int from, int to, int weight = 0);

    void removeEdge(int from, int to);

    int changeEdge(int from, int to, int newWeight);

    void load(std::ifstream &input);

    void dump(std::ofstream &output);

    ~GraphAsAdjList();
};


#endif //GRAPH_PROJECT_GRAPHASADJLIST_H
