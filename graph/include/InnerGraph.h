//
// Created by mick on 2/27/24.
//

#ifndef GRAPH_PROJECT_INNERGRAPH_H
#define GRAPH_PROJECT_INNERGRAPH_H

#include <fstream>

#define NOT_DIRECTED 0
#define DIRECTED 1
#define NOT_WEIGHTED 0
#define WEIGHTED 1

class InnerGraph {
protected:
    int size{};
    int weighted{};
    int directed{};

    virtual void init(int s, int d, int w) = 0;

public:
    virtual void addEdge(int from, int to, int weight) = 0;

    virtual void removeEdge(int from, int to) = 0;

    virtual int changeEdge(int from, int to, int newWeight) = 0;

    virtual void load(std::ifstream &input) = 0;

    virtual void dump(std::ofstream &output) = 0;
};

#endif //GRAPH_PROJECT_INNERGRAPH_H
