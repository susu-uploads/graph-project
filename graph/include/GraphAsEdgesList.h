//
// Created by mick on 2/26/24.
//

#ifndef GRAPH_PROJECT_GRAPHASEDGESLIST_H
#define GRAPH_PROJECT_GRAPHASEDGESLIST_H


#include <vector>
#include <fstream>
#include "Edge.h"

class GraphAsEdgesList {
protected:
    std::vector<Edge> holder;
    int size;
    int weighted;
    int directed;
public:
    void addEdge(int from, int to, int weight = 0);

    void removeEdge(int from, int to);

    int changeEdge(int from, int to, int newWeight);

    void load(std::ifstream &input);

    void dump(std::ofstream &output);

    ~GraphAsEdgesList();
};


#endif //GRAPH_PROJECT_GRAPHASEDGESLIST_H
