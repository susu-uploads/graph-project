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

void Graph::readGraph(const std::string &n) {
    // Open stream
    ifstream fileStream{n, ios_base::in};
    // Discovering what input pattern is
    char inputType;
    fileStream >> inputType;
    if (inputType == 'C') {
        representation = ADJUSTMENT_MATRIX;
        innerGraph = new GraphAsAdjMatrix;
    } else if (inputType == 'L') {
        representation = ADJUSTMENT_LIST;
        innerGraph = new GraphAsAdjList;
    } else if (inputType == 'E') {
        representation = EDGES_LIST;
        innerGraph = new GraphAsEdgesList;
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
    innerGraph->changeEdge(from, to, newWeight);
}

void Graph::transformToAdjMatrix() {
    auto new_graph = new GraphAsAdjMatrix;
    if (representation == ADJUSTMENT_LIST) {
        auto current_graph = dynamic_cast<GraphAsAdjList *>(innerGraph);
        new_graph->load(current_graph->size, current_graph->directed, current_graph->weighted, current_graph->holder);
        innerGraph = new_graph;
    } else if (representation == EDGES_LIST) {
        auto current_graph = dynamic_cast<GraphAsEdgesList *>(innerGraph);
        new_graph->load(current_graph->size, current_graph->directed, current_graph->weighted, current_graph->holder);
        innerGraph = new_graph;
    }
    representation = ADJUSTMENT_MATRIX;
}

void Graph::transformToAdjList() {
    auto new_graph = new GraphAsAdjList;
    if (representation == ADJUSTMENT_MATRIX) {
        auto current_graph = dynamic_cast<GraphAsAdjMatrix *>(innerGraph);
        new_graph->load(current_graph->size, current_graph->directed, current_graph->weighted, current_graph->holder);
        innerGraph = new_graph;
    } else if (representation == EDGES_LIST) {
        auto current_graph = dynamic_cast<GraphAsEdgesList *>(innerGraph);
        new_graph->load(current_graph->size, current_graph->directed, current_graph->weighted, current_graph->holder);
        innerGraph = new_graph;
    }
    representation = ADJUSTMENT_LIST;
}

void Graph::transformToListOfEdges() {
    auto new_graph = new GraphAsEdgesList;
    if (representation == ADJUSTMENT_MATRIX) {
        auto current_graph = dynamic_cast<GraphAsAdjMatrix *>(innerGraph);
        new_graph->load(current_graph->size, current_graph->directed, current_graph->weighted, current_graph->holder);
        innerGraph = new_graph;
    } else if (representation == ADJUSTMENT_LIST) {
        auto current_graph = dynamic_cast<GraphAsAdjList *>(innerGraph);
        new_graph->load(current_graph->size, current_graph->directed, current_graph->weighted, current_graph->holder);
        innerGraph = new_graph;
    }
    representation = EDGES_LIST;
}

void Graph::writeGraph(const std::string &fileName) {
    ofstream fileStream{fileName, ios_base::out};
    if (representation == ADJUSTMENT_MATRIX) {
        fileStream << 'C' << ' ';
    } else if (representation == ADJUSTMENT_LIST) {
        fileStream << 'L' << ' ';
    } else if (representation == EDGES_LIST) {
        fileStream << 'E' << ' ';
    }
    innerGraph->dump(fileStream);
}