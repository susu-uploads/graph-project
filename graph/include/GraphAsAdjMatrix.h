//
// Created by mick on 2/26/24.
//

#ifndef GRAPH_PROJECT_GRAPHASADJMATRIX_H
#define GRAPH_PROJECT_GRAPHASADJMATRIX_H


#include <vector>
#include <fstream>
#include "InnerGraph.h"

class GraphAsAdjMatrix : public InnerGraph {
public:
    std::vector<std::vector<int>> holder;

    void init(int s, int d, int w) override;

    void addEdge(int from, int to, int weight) override;

    void removeEdge(int from, int to) override;

    int changeEdge(int from, int to, int newWeight) override;

    void load(std::ifstream &input) override;

    void dump(std::ofstream &output) override;

    void load(int s, int d, int w, const std::vector<Edge> &data);

    void load(int s, int d, int w, const std::vector<Node> &data);
};


#endif //GRAPH_PROJECT_GRAPHASADJMATRIX_H
