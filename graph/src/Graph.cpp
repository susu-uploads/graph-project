//
// Created by mick on 12.02.2024.
//

#include <fstream>
#include "../include/Graph.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <set>
#include <stdexcept>
#include <unistd.h>

#include "DSU.h"
#include "Euler.h"
#include "MST.h"

using namespace std;

Graph::Graph() : representation(EDGES_LIST) {
    innerGraph = new GraphAsEdgesList;
    innerGraph->size = 0;
    innerGraph->directed = NOT_DIRECTED;
    innerGraph->weighted = WEIGHTED;
}

Graph::Graph(const int size) : representation(EDGES_LIST) {
    innerGraph = new GraphAsEdgesList;
    innerGraph->size = size;
    innerGraph->directed = NOT_DIRECTED;
    innerGraph->weighted = WEIGHTED;
}

void Graph::readGraph(const std::string &fileName) {
    ifstream fileStream{fileName, ios_base::in};
    char inputType;
    fileStream >> inputType;
    if (inputType == ADJUSTMENT_MATRIX_INDICATOR) {
        representation = ADJUSTMENT_MATRIX;
        innerGraph = new GraphAsAdjMatrix;
    } else if (inputType == ADJUSTMENT_LIST_INDICATOR) {
        representation = ADJUSTMENT_LIST;
        innerGraph = new GraphAsAdjList;
    } else if (inputType == EDGES_LIST_INDICATOR) {
        representation = EDGES_LIST;
        innerGraph = new GraphAsEdgesList;
    } else {
        throw invalid_argument("Unrecognizable format: " + to_string(inputType));
    }
    innerGraph->load(fileStream);
}

void Graph::addEdge(const int from, const int to, const int weight) const {
    innerGraph->addEdge(from, to, weight);
}

void Graph::removeEdge(const int from, const int to) const {
    innerGraph->removeEdge(from, to);
}

int Graph::changeEdge(const int from, const int to, const int newWeight) const {
    return innerGraph->changeEdge(from, to, newWeight);
}

void Graph::transformToAdjMatrix() {
    if (representation == ADJUSTMENT_MATRIX) {
        return;
    }
    const auto new_graph = new GraphAsAdjMatrix;
    if (representation == ADJUSTMENT_LIST) {
        const auto adjl_graph = dynamic_cast<GraphAsAdjList *>(innerGraph);
        new_graph->load(adjl_graph->size, adjl_graph->directed, adjl_graph->weighted, adjl_graph->holder);
    } else if (representation == EDGES_LIST) {
        const auto edjl_graph = dynamic_cast<GraphAsEdgesList *>(innerGraph);
        new_graph->load(edjl_graph->size, edjl_graph->directed, edjl_graph->weighted, edjl_graph->holder);
    }
    innerGraph = new_graph;
    representation = ADJUSTMENT_MATRIX;
}

void Graph::transformToAdjList() {
    if (representation == ADJUSTMENT_LIST) {
        return;
    }
    const auto new_graph = new GraphAsAdjList;
    if (representation == ADJUSTMENT_MATRIX) {
        const auto adjm_graph = dynamic_cast<GraphAsAdjMatrix *>(innerGraph);
        new_graph->load(adjm_graph->size, adjm_graph->directed, adjm_graph->weighted, adjm_graph->holder);
    } else if (representation == EDGES_LIST) {
        const auto edjl_graph = dynamic_cast<GraphAsEdgesList *>(innerGraph);
        new_graph->load(edjl_graph->size, edjl_graph->directed, edjl_graph->weighted, edjl_graph->holder);
    }
    innerGraph = new_graph;
    representation = ADJUSTMENT_LIST;
}

void Graph::transformToListOfEdges() {
    if (representation == EDGES_LIST) {
        return;
    }
    const auto new_graph = new GraphAsEdgesList;
    if (representation == ADJUSTMENT_MATRIX) {
        const auto adjm_graph = dynamic_cast<GraphAsAdjMatrix *>(innerGraph);
        new_graph->load(adjm_graph->size, adjm_graph->directed, adjm_graph->weighted, adjm_graph->holder);
    } else if (representation == ADJUSTMENT_LIST) {
        const auto adjl_graph = dynamic_cast<GraphAsAdjList *>(innerGraph);
        new_graph->load(adjl_graph->size, adjl_graph->directed, adjl_graph->weighted, adjl_graph->holder);
    }
    innerGraph = new_graph;
    representation = EDGES_LIST;
}

void Graph::writeGraph(const std::string &fileName) const {
    ofstream fileStream{fileName, ios_base::out};
    if (representation == ADJUSTMENT_MATRIX) {
        fileStream << ADJUSTMENT_MATRIX_INDICATOR << ' ';
    } else if (representation == ADJUSTMENT_LIST) {
        fileStream << ADJUSTMENT_LIST_INDICATOR << ' ';
    } else if (representation == EDGES_LIST) {
        fileStream << EDGES_LIST_INDICATOR << ' ';
    }
    innerGraph->dump(fileStream);
}

Graph Graph::getSpaingTreePrima() {
    this->transformToAdjList();
    const auto representation = dynamic_cast<GraphAsAdjList *>(innerGraph);
    const Graph mst(representation->size);
    make_prima_mst(mst, representation->size, representation->holder);
    return mst;
}

Graph Graph::getSpaingTreeKruscal() {
    this->transformToListOfEdges();
    const auto representation = dynamic_cast<GraphAsEdgesList *>(innerGraph);
    const Graph mst(representation->size);
    make_kruskal_mst(mst, representation->size, representation->holder);
    return mst;
}

Graph Graph::getSpaingTreeBoruvka() {
    this->transformToListOfEdges();
    const auto representation = dynamic_cast<GraphAsEdgesList *>(innerGraph);
    const Graph mst(representation->size);
    make_boruvka_mst(mst, representation->size, representation->holder);
    return mst;
}

int Graph::checkEuler(bool &circleExist) {
    this->transformToAdjList();
    const auto adjl_graph = dynamic_cast<GraphAsAdjList *>(innerGraph);
    try {
        const auto [vertice, isExist] = find_vertice(adjl_graph->holder);
        circleExist = isExist;
        return vertice + 1;
    } catch (std::invalid_argument &exception) {
        circleExist = false;
        return 0;
    }
}

std::vector<int> Graph::getEuleranTourFleri() const {
    const auto adjl_graph = dynamic_cast<GraphAsAdjList *>(innerGraph);
    auto vertices = vector(adjl_graph->holder);
    return find_euler_tour_fluery(vertices, adjl_graph->directed);
}

std::vector<int> Graph::getEuleranTourEffective() {
}
