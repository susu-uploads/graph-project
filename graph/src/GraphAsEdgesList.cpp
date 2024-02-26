//
// Created by mick on 2/26/24.
//

#include "GraphAsEdgesList.h"

void GraphAsEdgesList::addEdge(int from, int to, int weight) {

}

void GraphAsEdgesList::removeEdge(int from, int to) {

}

int GraphAsEdgesList::changeEdge(int from, int to, int newWeight) {
    return 0;
}

void GraphAsEdgesList::load(std::ifstream &input) {
    int N, M, D, W;
    input >> N >> M >> D >> W;
    size = N;
    directed = D;
    weighted = W;
    if (weighted == 0) {
        int a, b;
        while (M-- > 0) {
            input >> a >> b;
            holder.emplace_back(a, b);
            if (directed == 0) {
                holder.emplace_back(b, a);
            }
        }
    } else {
        int a, b, w;
        while (M-- > 0) {
            input >> a >> b >> w;
            holder.emplace_back(a, b, w);
            if (directed == 0) {
                holder.emplace_back(b, a, w);
            }
        }
    }
}

void GraphAsEdgesList::dump(std::ofstream &output) {
    int edges_count = holder.size();
    if (directed == 0) {
        edges_count /= 2;
    }
    output << size << ' ' << edges_count << '\n';
    output << directed << ' ' << weighted << '\n';
    bool print = true;
    for (Edge edge : holder) {
        if (print) {
            output << edge.from << ' ';
            output << edge.to << ' ';
            if (weighted) {
                output << edge.weight;
            }
            output << '\n';
        }
        print = !print;
    }
}

GraphAsEdgesList::~GraphAsEdgesList() = default;
