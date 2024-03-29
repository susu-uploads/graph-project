#include <iostream>
#include "graph/include/Graph.h"

using namespace std;

#define IN "/home/mick/CLionProjects/graph-project/res/in"
#define OUT_1 "/home/mick/CLionProjects/graph-project/res/out_1"
#define OUT_2 "/home/mick/CLionProjects/graph-project/res/out_2"
#define OUT_3 "/home/mick/CLionProjects/graph-project/res/out_3"

void test_with_my_graph();

void test_with_given_graph();

int main() {
    test_with_given_graph();
    return 0;
}

void test_with_my_graph() {
    Graph graph;
    graph.readGraph(IN);
    graph.transformToListOfEdges();
    graph.writeGraph(OUT_1);
    graph.transformToAdjList();
    graph.writeGraph(OUT_2);
    graph.transformToAdjMatrix();
    graph.writeGraph(OUT_3);
}

void test_with_given_graph() {
    Graph graph;
    graph.readGraph("/home/mick/CLionProjects/graph-project/res/input_1e3_1e5.txt");
    graph.transformToListOfEdges();
    graph.transformToAdjList();
    graph.transformToAdjMatrix();
    graph.transformToListOfEdges();
    graph.writeGraph("/home/mick/CLionProjects/graph-project/res/output_1e3_1e5.txt");
}
