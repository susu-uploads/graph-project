//
// Created by mick on 2/26/24.
//

#ifndef GRAPH_PROJECT_GRAPHASADJLIST_H
#define GRAPH_PROJECT_GRAPHASADJLIST_H


#include <vector>
#include <fstream>
#include "Node.h"
#include "InnerGraph.h"

class GraphAsAdjList : protected InnerGraph {
private:
    std::vector<Node> holder;
public:
    void addEdge(int from, int to, int weight) override;

    void removeEdge(int from, int to) override;

    int changeEdge(int from, int to, int newWeight) override;

    void load(std::ifstream &input) override;

    void dump(std::ofstream &output) override;
};


#endif //GRAPH_PROJECT_GRAPHASADJLIST_H
