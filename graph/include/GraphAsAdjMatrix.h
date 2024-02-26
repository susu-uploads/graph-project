//
// Created by mick on 2/26/24.
//

#ifndef GRAPH_PROJECT_GRAPHASADJMATRIX_H
#define GRAPH_PROJECT_GRAPHASADJMATRIX_H


#include <vector>
#include <fstream>

class GraphAsAdjMatrix {
protected:
    std::vector<std::vector<int>> adjustmentMatrix;
    int size;
    int weighted;
    int directed;
public:
    void addEdge(int from, int to, int weight = 0);

    void removeEdge(int from, int to);

    int changeEdge(int from, int to, int newWeight);

    void load(std::ifstream &input);

    void dump(std::ofstream &output);

    ~GraphAsAdjMatrix();
};


#endif //GRAPH_PROJECT_GRAPHASADJMATRIX_H
