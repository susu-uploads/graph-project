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
public:
    int size{};
    int weighted{};
    int directed{};

    virtual void addEdge(int from, int to, int weight) {}

    virtual void removeEdge(int from, int to) {}

    virtual int changeEdge(int from, int to, int newWeight) {}

    virtual void load(std::ifstream &input) {}

    virtual void dump(std::ofstream &output) {}

protected:
    virtual void init(int s, int d, int w) {}

};

#endif //GRAPH_PROJECT_INNERGRAPH_H
