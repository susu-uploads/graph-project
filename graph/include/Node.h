//
// Created by mick on 2/14/24.

#ifndef GRAPH_PROJECT_NODE_H
#define GRAPH_PROJECT_NODE_H

#include <map>

/**
 * Struct used to describe node of graph with binded children nodes.
 */
struct Node {
    int name;
    std::map<int, int> children{};

    /**
     * Create node with name.
     * @param name Node name.
     */
    explicit Node(int name);

    /**
     * Bind node with other via path with weight.
     * @param vertice Binded node name.
     * @param weight Path weight.
     */
    void connect(int vertice, int weight = 1);

    /**
     * Re-bind node with other via path with weight.
     * @param vertice Binded node name.
     * @param new_weight Path weight.
     * @return Old weight.
     */
    int rebalance(int vertice, int new_weight);
};

#endif //GRAPH_PROJECT_NODE_H
