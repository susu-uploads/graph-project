#include <iostream>
#include "graph/include/Graph.h"

using namespace std;

#define EDGES_LIST_1 "/home/mick/CLionProjects/graph-project/res/input_1e3_1e5.txt"
#define EDGES_LIST_2 "/home/mick/CLionProjects/graph-project/res/input_1e4_1e5.txt"
#define EDGES_LIST_3 "/home/mick/CLionProjects/graph-project/res/input_1e5_1e5.txt"

#define IN "/home/mick/CLionProjects/graph-project/res/in"

#define OUT_1 "/home/mick/CLionProjects/graph-project/res/out_1"
#define OUT_2 "/home/mick/CLionProjects/graph-project/res/out_2"
#define OUT_3 "/home/mick/CLionProjects/graph-project/res/out_3"

void test_1();

void test_2();

void test_3();

int main() {
    test_1();
    std::cout << "1 done" << std::endl;
    test_2();
    std::cout << "2 done" << std::endl;
    test_3();
    std::cout << "3 done" << std::endl;
    return 0;
}

void test_1() {
    Graph g;
    g.readGraph(EDGES_LIST_1);
    g.transformToAdjMatrix();
    g.transformToAdjList();
    g.transformToListOfEdges();
    g.writeGraph(OUT_1);
}

void test_2() {
    Graph g;
    g.readGraph(OUT_1);
    g.transformToAdjList();
    g.writeGraph(OUT_2);
}

void test_3() {
    Graph g;
    g.readGraph(OUT_2);
    g.transformToListOfEdges();
    g.writeGraph(OUT_3);
}
