//
// Created by mick on 2/14/24.
//

#include <Node.h>

Node::Node(int name) : name(name) {}

void Node::connect(int vertice, int weight) {
    this->children.insert(vertice, weight);
}

int Node::rebalance(int vertice, int new_weight) {
    int old_weight = -1;
    auto node = children.find(vertice);
    if (node != children.end()) {
        old_weight = node->second;
        node->second = new_weight;
    }
    return old_weight;
}

