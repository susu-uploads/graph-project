//
// Created by mick on 2/26/24.
//

#include "GraphAsAdjList.h"

void GraphAsAdjList::addEdge(int from, int to, int weight) {

}

void GraphAsAdjList::removeEdge(int from, int to) {

}

int GraphAsAdjList::changeEdge(int from, int to, int newWeight) {
    return 0;
}

void GraphAsAdjList::load(std::ifstream &input) {
    int N, D, W;
    input >> N >> D >> W;
    size = N;
    directed = D;
    weighted = W;
    for (int i = 0; i < N; i++) {
        holder.emplace_back(i);
    }
    // TODO
}

void GraphAsAdjList::dump(std::ofstream &output) {
    // TODO
}

GraphAsAdjList::~GraphAsAdjList() = default;
