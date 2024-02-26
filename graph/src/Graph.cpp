//
// Created by mick on 12.02.2024.
//

#include <fstream>
#include <functional>
#include "../include/Graph.h"

using namespace std;

void Graph::readGraph(const std::string &fileName) {
    // Open stream
    ifstream fileStream{fileName, ios_base::in};

    // Discovering what input pattern is
    char inputType;
    fileStream >> inputType;
    if (inputType == 'C') {
        representation = 0;
        graphAsAdjMatrix.load(fileStream);
    } else if (inputType == 'L') {
        representation = 1;
        graphAsAdjList.load(fileStream);
    } else if (inputType == 'E') {
        representation = 2;
        graphAsEdgesList.load(fileStream);
    } else {
        throw invalid_argument("Unrecognizable format: " + to_string(inputType));
    }
}

void Graph::addEdge(int from, int to, int weight) {
    // TODO
}

void Graph::removeEdge(int from, int to) {
    // TODO
}

int Graph::changeEdge(int from, int to, int newWeight) {
    // TODO
    return 0;
}

void Graph::transformToAdjMatrix() {
    representation = 0;
}

void Graph::transformToAdjList() {
    representation = 1;
}

void Graph::transformToListOfEdges() {
    representation = 2;
}

void Graph::writeGraph(const std::string &fileName) {
    ofstream fileStream{fileName, ios_base::out};
    if (representation == 0) {
        fileStream << 'C' << ' ';
        graphAsAdjMatrix.dump(fileStream);
    } else if (representation == 1) {
        fileStream << 'L' << ' ';
        graphAsAdjList.dump(fileStream);
    } else if (representation == 2) {
        fileStream << 'E' << ' ';
        graphAsEdgesList.dump(fileStream);
    } else {
        throw invalid_argument("Unrecognizable format: " + to_string(representation));
    }
}