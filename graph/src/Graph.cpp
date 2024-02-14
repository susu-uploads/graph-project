//
// Created by mick on 12.02.2024.
//

#include <fstream>
#include <functional>
#include "../include/Graph.h"

using namespace std;

// ----------------------- Internal load functions -----------------------
void load_as_list_of_edges(Graph &graph, std::ifstream &input, const function<void(const int)> &resize);

void load_as_adjustment_matrix(Graph &graph, ifstream &input, const function<void(const int)> &resize);

void load_as_adjustment_list(Graph &graph, ifstream &input, const function<void(const int)> &resize);

// ----------------------- Graph -----------------------
void Graph::readGraph(const std::string &fileName) {
    // Open stream
    ifstream fileStream{fileName, ios_base::in};

    // Prepare callback for size
    auto lambda = [&](const int n) {
        adjustmentList.resize(n, {});
        adjustmentMatrix.resize(n, {n});
        edgesList.resize(n);
    };

    // Discovering what input pattern is
    char inputType;
    fileStream >> inputType;
    if (inputType == 'E') {
        representationType = 2;
        load_as_list_of_edges(*this, fileStream, lambda);
    } else if (inputType == 'C') {
        representationType = 1;
        load_as_adjustment_matrix(*this, fileStream, lambda);
    } else if (inputType == 'L') {
        representationType = 0;
        load_as_adjustment_list(*this, fileStream, lambda);
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
    return 0;
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
    ofstream fileStream{fileName, ios_base::out};
    fileStream << "";
}


void load_as_list_of_edges(Graph &graph, std::ifstream &input, const function<void(const int)> &resize) {
    int N, M, D, W;
    input >> N >> M >> D >> W;
    resize(N);
    if (W == 0) {
        int a, b, w;
        while (M-- > 0) {
            input >> a >> b >> w;
            graph.addEdge(a, b, w);
            if (D == 0) {
                graph.addEdge(b, a, w);
            }
        }
    } else {
        int a, b;
        while (M-- > 0) {
            input >> a >> b;
            graph.addEdge(a, b, 1);
            if (D == 0) {
                graph.addEdge(b, a, 1);
            }
        }
    }

}

void load_as_adjustment_matrix(Graph &graph, ifstream &input, const function<void(const int)> &resize) {
    // TODO
}

void load_as_adjustment_list(Graph &graph, ifstream &input, const function<void(const int)> &resize) {
    // TODO
}
