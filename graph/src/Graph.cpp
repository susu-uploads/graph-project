//
// Created by mick on 12.02.2024.
//

#include <GraphIoHelper.h>
#include "../include/Graph.h"

using namespace std;

void Graph::readGraph(const std::string &fileName) {
    GraphIoHelper::load_from_file(*this, fileName);
}

void Graph::addEdge(int from, int to, int weight) {
    // TODO
}

void Graph::removeEdge(int from, int to) {
    // TODO
}

int Graph::changeEdge(int from, int to, int newWeight) {
    auto edge = internal_representation[from][to];
    auto oldWeight = edge.second;
    edge.second = newWeight;
    return oldWeight;
}

void Graph::transformToAdjList() {
    representationType = 0;
}

void Graph::transformToAdjMatrix() {
    representationType = 1;
}

void Graph::transformToListOfEdges() {
    representationType = 2;
}

void Graph::writeGraph(const std::string &fileName) {
    GraphIoHelper::dump_to_file(*this, fileName, representationType);
}
