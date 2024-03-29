//
// Created by mick on 2/14/24.

#ifndef GRAPH_PROJECT_EDGE_H
#define GRAPH_PROJECT_EDGE_H

/**
 * Struct used to describe an edge between vertices with or without weight.
 */
struct Edge {
    int from, to, weight;

    Edge(int u, int v, int length = 1);

    friend bool operator<(const Edge &lhs, const Edge &rhs);

    friend bool operator<=(const Edge &lhs, const Edge &rhs);

    friend bool operator>(const Edge &lhs, const Edge &rhs);

    friend bool operator>=(const Edge &lhs, const Edge &rhs);
};

#endif //GRAPH_PROJECT_EDGE_H
