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
        c.load(fileStream);
    } else if (inputType == 'L') {
        representation = ADJUSTMENT_LIST;
        viewer = ADJUSTMENT_LIST;
        l.load(fileStream);
    } else if (inputType == 'E') {
        representation = EDGES_LIST;
        viewer = EDGES_LIST;
        e.load(fileStream);
    } else {
        throw invalid_argument("Unrecognizable format: " + to_string(inputType));
    }
}

void Graph::addEdge(int from, int to, int weight) {
    if (representation == ADJUSTMENT_MATRIX) {
        c.addEdge(from, to, weight);
    } else if (representation == ADJUSTMENT_LIST) {
        l.addEdge(from, to, weight);
    } else if (representation == EDGES_LIST) {
        e.addEdge(from, to, weight);
    } else {
        throw invalid_argument("Unrecognizable format: " + to_string(representation));
    }
}

void Graph::removeEdge(int from, int to) {
    if (representation == ADJUSTMENT_MATRIX) {
        c.removeEdge(from, to);
    } else if (representation == ADJUSTMENT_LIST) {
        l.removeEdge(from, to);
    } else if (representation == EDGES_LIST) {
        e.removeEdge(from, to);
    } else {
        throw invalid_argument("Unrecognizable format: " + to_string(representation));
    }
}

int Graph::changeEdge(int from, int to, int newWeight) {
    if (representation == ADJUSTMENT_MATRIX) {
        return c.changeEdge(from, to, newWeight);
    } else if (representation == ADJUSTMENT_LIST) {
        return l.changeEdge(from, to, newWeight);
    } else if (representation == EDGES_LIST) {
        return e.changeEdge(from, to, newWeight);
    } else {
        throw invalid_argument("Unrecognizable format: " + to_string(representation));
    }
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
        if (representation == ADJUSTMENT_LIST) {
            c.load(l.size, l.directed, l.weighted, l.holder);
            c.dump(fileStream);
        } else if (representation == EDGES_LIST) {
            c.load(e.size, e.directed, e.weighted, e.holder);
            c.dump(fileStream);
        } else {
            c.dump(fileStream);
        }
        representation = ADJUSTMENT_MATRIX;
    } else if (viewer == ADJUSTMENT_LIST) {
        fileStream << 'L' << ' ';
        if (representation == ADJUSTMENT_MATRIX) {
            l.load(c.size, c.directed, c.weighted, c.holder);
            l.dump(fileStream);
        } else if (representation == EDGES_LIST) {
            l.load(e.size, e.directed, e.weighted, e.holder);
            l.dump(fileStream);
        } else {
            l.dump(fileStream);
        }
        representation = ADJUSTMENT_LIST;
    } else if (viewer == EDGES_LIST) {
        fileStream << 'E' << ' ';
        if (representation == ADJUSTMENT_MATRIX) {
            e.load(c.size, c.directed, c.weighted, c.holder);
            e.dump(fileStream);
        } else if (representation == ADJUSTMENT_LIST) {
            e.load(l.size, l.directed, l.weighted, l.holder);
            e.dump(fileStream);
        } else {
            e.dump(fileStream);
        }
        representation = EDGES_LIST;
    } else {
        throw invalid_argument("Unrecognizable format: " + to_string(representation));
    }
}