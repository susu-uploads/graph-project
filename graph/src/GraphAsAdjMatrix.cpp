//
// Created by mick on 2/26/24.
//

#include <Edge.h>
#include <Node.h>
#include "GraphAsAdjMatrix.h"

using namespace std;

void GraphAsAdjMatrix::addEdge(const int from, const int to, const int weight) {
    holder[from][to] = weight;
}

void GraphAsAdjMatrix::removeEdge(const int from, const int to) {
    holder[from][to] = 0;
}

int GraphAsAdjMatrix::changeEdge(const int from, const int to, const int newWeight) {
    int old_weight = holder[from][to];
    holder[from][to] = newWeight;
    return old_weight;
}

void GraphAsAdjMatrix::load(std::ifstream &input) {
    int N, D, W;
    input >> N >> D >> W;
    init(N, D, W);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int weight;
            input >> weight;
            addEdge(i, j, weight);
        }
    }
}

void GraphAsAdjMatrix::dump(std::ofstream &output) {
    output << size << '\n';
    output << directed << ' ' << weighted << '\n';
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            output << holder[i][j];
            if (j != size - 1) {
                output << ' ';
            }
        }
        output << '\n';
    }
}

void GraphAsAdjMatrix::init(const int s, const int d, const int w) {
    size = s;
    directed = d;
    weighted = w;
    holder.clear();
    holder.resize(s, vector<int>(s));
}

void GraphAsAdjMatrix::load(const int s, const int d, const int w, const std::vector<Edge> &data) {
    init(s, d, w);
    if (directed == NOT_DIRECTED) {
        for (const Edge edge : data) {
            addEdge(edge.from, edge.to, edge.weight);
            addEdge(edge.to, edge.from, edge.weight);
        }
    } else if (directed == DIRECTED) {
        for (const Edge edge : data) {
            addEdge(edge.from, edge.to, edge.weight);
        }
    }
}

void GraphAsAdjMatrix::load(const int s, const int d, const int w, const std::vector<Node> &data) {
    init(s, d, w);
    for (const auto &node : data) {
        for (auto connection : node.children) {
            addEdge(node.name, connection.first, connection.second);
        }
    }
}
