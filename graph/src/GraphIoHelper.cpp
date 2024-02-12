//
// Created by mick on 12.02.2024.
//

#include <fstream>
#include <string>
#include "GraphIoHelper.h"

using namespace std;

void GraphIoHelper::load_from_file(Graph &graph, const std::string &fileName) {
    // Open stream
    ifstream fileStream{fileName, ios_base::in};

    // Discovering what input pattern is
    char inputType;
    fileStream >> inputType;
    if (inputType == 'E') {
        load_as_list_of_edges(graph, fileStream);
    } else if (inputType == 'C') {
        load_as_adjustment_matrix(graph, fileStream);
    } else if (inputType == 'L') {
        load_as_adjustment_list(graph, fileStream);
    } else {
        throw invalid_argument("Unrecognizable format: " + to_string(inputType));
    }
}

void GraphIoHelper::dump_to_file(Graph &graph, const std::string &fileName, int format) {
    ofstream fileStream{fileName, ios_base::out};
    fileStream << "";
}

void GraphIoHelper::load_as_list_of_edges(Graph &graph, std::ifstream &input) {
    int N, M, D, W;
    input >> N >> M >> D >> W;
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

void GraphIoHelper::load_as_adjustment_matrix(Graph &graph, ifstream &input) {
    // TODO
}

void GraphIoHelper::load_as_adjustment_list(Graph &graph, ifstream &input) {
    // TODO
}
