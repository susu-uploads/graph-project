//
// Created by mick on 2/14/24.
//

#ifndef GRAPH_PROJECT_NODE_H
#define GRAPH_PROJECT_NODE_H

#include <map>

struct Node {
    int name;
    std::map<int, int> children{};

    explicit Node(int name);

    void connect(int vertice, int weight = 0);

    int rebalance(int vertice, int new_weight);
};

#endif //GRAPH_PROJECT_NODE_H
