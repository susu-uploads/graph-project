//
// Created by mick on 2/26/24.
//

#include "GraphAsAdjMatrix.h"

void GraphAsAdjMatrix::addEdge(int from, int to, int weight) {

}

void GraphAsAdjMatrix::removeEdge(int from, int to) {

}

int GraphAsAdjMatrix::changeEdge(int from, int to, int newWeight) {
    return 0;
}

void GraphAsAdjMatrix::load(std::ifstream &input) {
    int N, M, D, W;
    input >> N >> M >> D >> W;
    size = N;
    directed = D;
    weighted = W;
    // TODO
}

void GraphAsAdjMatrix::dump(std::ofstream &output) {
    // TODO
}

GraphAsAdjMatrix::~GraphAsAdjMatrix() = default;
