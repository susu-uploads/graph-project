//
// Created by mick on 2/14/24.
//

#include <Node.h>

Node::Node(int name) : name(name) {}

void Node::connect(int v, int weight) {
    this->children.emplace_back(name, v, weight);
}

int Node::rebalance(int vertice, int new_weight) {
    for (auto edge : children) {
        int weight = edge.weight;
        if (edge.to == vertice) {
            edge.weight = new_weight;
            return weight;
        }
    }
    return -1;
}

