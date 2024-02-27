//
// Created by mick on 2/26/24.
//

#include "GraphAsAdjMatrix.h"

using namespace std;

void GraphAsAdjMatrix::addEdge(int from, int to, int weight) {
    holder[from][to] = weight;
}

void GraphAsAdjMatrix::removeEdge(int from, int to) {
    holder[from][to] = 0;
}

int GraphAsAdjMatrix::changeEdge(int from, int to, int newWeight) {
    int old_weight = holder[from][to];
    holder[from][to] = newWeight;
    return old_weight;
}

void GraphAsAdjMatrix::load(std::ifstream &input) {
    int N, D, W;
    input >> N >> D >> W;
    size = N;
    directed = D;
    weighted = W;
    holder.resize(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            input >> holder[i][j];
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
