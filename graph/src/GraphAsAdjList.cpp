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
    int N, M, D, W;
    input >> N >> M >> D >> W;
    size = N;
    directed = D;
    weighted = W;
    // TODO
}

void GraphAsAdjList::dump(std::ofstream &output) {
    // TODO
}

GraphAsAdjList::~GraphAsAdjList() = default;
