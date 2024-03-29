//
// Created by mick on 2/14/24.
//

#include <Edge.h>

Edge::Edge(const int u, const int v, const int length) : from(u), to(v), weight(length) {}

bool operator<(const Edge &lhs, const Edge &rhs) {
    return lhs.weight < rhs.weight;
}

bool operator<=(const Edge &lhs, const Edge &rhs) {
    return lhs.weight <= rhs.weight;
}

bool operator>(const Edge &lhs, const Edge &rhs) {
    return lhs.weight > rhs.weight;
}

bool operator>=(const Edge &lhs, const Edge &rhs) {
    return lhs.weight >= rhs.weight;
}
