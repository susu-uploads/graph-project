//
// Created by mick on 2/14/24.
//

#ifndef GRAPH_PROJECT_NODE_H
#define GRAPH_PROJECT_NODE_H

#include <vector>
#include "Edge.h"

struct Node {
    int name;
    std::vector<Edge> children{};

    explicit Node(int name);

    void connect(int v, int weight = 1);

    int rebalance(int vertice, int new_weight);
};

#endif //GRAPH_PROJECT_NODE_H
