//
// Created by mick on 12.02.2024.
//

#ifndef GRAPH_PROJECT_GRAPHIOHELPER_H
#define GRAPH_PROJECT_GRAPHIOHELPER_H

#include <string>
#include "Graph.h"

class GraphIoHelper {
public:
    static void load_from_file(Graph &graph, const std::string &fileName);

    static void dump_to_file(Graph &graph, const std::string &fileName, int format);

private:
    static void load_as_list_of_edges(Graph &graph, std::ifstream &input);

    static void load_as_adjustment_matrix(Graph &graph, std::ifstream &input);

    static void load_as_adjustment_list(Graph &graph, std::ifstream &input);
};


#endif //GRAPH_PROJECT_GRAPHIOHELPER_H
