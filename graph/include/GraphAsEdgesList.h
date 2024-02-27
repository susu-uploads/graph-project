//
// Created by mick on 2/26/24.
//

#ifndef GRAPH_PROJECT_GRAPHASEDGESLIST_H
#define GRAPH_PROJECT_GRAPHASEDGESLIST_H


#include <vector>
#include <fstream>
#include "Edge.h"
#include "Node.h"
#include "InnerGraph.h"

class GraphAsEdgesList : protected InnerGraph {
private:
    std::vector<Edge> holder;
public:
    void addEdge(int from, int to, int weight) override;

    void removeEdge(int from, int to) override;

    int changeEdge(int from, int to, int newWeight) override;

    void load(std::ifstream &input) override;

    void dump(std::ofstream &output) override;

    void from(const std::vector<Node>& data, int s, int w, int d);

    void from(const std::vector<std::vector<int>>& data, int s, int w, int d);
};


#endif //GRAPH_PROJECT_GRAPHASEDGESLIST_H
