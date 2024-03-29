//
// Created by mick on 2/14/24.
//

#include <Node.h>

Node::Node(const int name) : name(name) {}

void Node::connect(int vertice, int weight) {
    this->children.insert(std::pair{vertice, weight});
}

int Node::rebalance(const int vertice, const int new_weight) {
    auto pair = children.find(vertice);
    int old_weight = pair->second;
    pair->second = new_weight;
    return old_weight;
}
