//
// Created by mick on 12.02.2024.
//

#include <fstream>
#include <functional>
#include "../include/Graph.h"

#define ADJUSTMENT_MATRIX 0
#define ADJUSTMENT_LIST 1
#define EDGES_LIST 2

using namespace std;

void Graph::readGraph(const std::string &fileName) {
    // Open stream
    ifstream fileStream{fileName, ios_base::in};
    // Discovering what input pattern is
    char inputType;
    fileStream >> inputType;
    if (inputType == 'C') {
        representation = ADJUSTMENT_MATRIX;
        viewer = ADJUSTMENT_MATRIX;
        auto g = GraphAsAdjMatrix{};
        innerGraph = &g;
    } else if (inputType == 'L') {
        representation = ADJUSTMENT_LIST;
        viewer = ADJUSTMENT_LIST;
        auto g = GraphAsAdjList{};
        innerGraph = &g;
    } else if (inputType == 'E') {
        representation = EDGES_LIST;
        viewer = EDGES_LIST;
        auto g = GraphAsEdgesList{};
        innerGraph = &g;
    } else {
        throw invalid_argument("Unrecognizable format: " + to_string(inputType));
    }
    innerGraph->load(fileStream);
}

void Graph::addEdge(int from, int to, int weight) {
    innerGraph->addEdge(from, to, weight);
}

void Graph::removeEdge(int from, int to) {
    innerGraph->removeEdge(from, to);
}

int Graph::changeEdge(int from, int to, int newWeight) {
    return innerGraph->changeEdge(from, to, newWeight);
}

void Graph::transformToAdjMatrix() {
    viewer = ADJUSTMENT_MATRIX;
}

void Graph::transformToAdjList() {
    viewer = ADJUSTMENT_LIST;
}

void Graph::transformToListOfEdges() {
    viewer = EDGES_LIST;
}

void Graph::writeGraph(const std::string &fileName) {
    ofstream fileStream{fileName, ios_base::out};
    if (viewer == ADJUSTMENT_MATRIX) {
        fileStream << 'C' << ' ';
        // TODO
    } else if (viewer == ADJUSTMENT_LIST) {
        fileStream << 'L' << ' ';
        // TODO
    } else if (viewer == EDGES_LIST) {
        fileStream << 'E' << ' ';
        // TODO
    } else {
        throw invalid_argument("Unrecognizable format: " + to_string(representation));
    }
    innerGraph->dump(fileStream);
}