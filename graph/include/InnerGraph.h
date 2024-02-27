//
// Created by mick on 2/27/24.
//

#ifndef GRAPH_PROJECT_INNERGRAPH_H
#define GRAPH_PROJECT_INNERGRAPH_H

#include <fstream>

class InnerGraph {
protected:
    int size{};
    int weighted{};
    int directed{};
public:
    virtual void addEdge(int from, int to, int weight) = 0;

    virtual void removeEdge(int from, int to) = 0;

    virtual int changeEdge(int from, int to, int newWeight) = 0;

    virtual void load(std::ifstream &input) = 0;

    virtual void dump(std::ofstream &output) = 0;
};

#endif //GRAPH_PROJECT_INNERGRAPH_H
