#include <cassert>
#include <iostream>
#include <queue>

#include "graph/include/Graph.h"
#include "graph/include/DSU.h"

using namespace std;

#define IN "/home/mick/CLionProjects/graph-project/res/in"
#define OUT_1 "/home/mick/CLionProjects/graph-project/res/out_1"
#define OUT_2 "/home/mick/CLionProjects/graph-project/res/out_2"
#define OUT_3 "/home/mick/CLionProjects/graph-project/res/out_3"

void test_with_my_graph();

void test_with_given_graph();

void test_dsu();

void test_mst();

void inner_test_mst();

void test_priority_queue();

int main() {
    inner_test_mst();
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

void test_dsu() {
    auto dsu = DSU(10);
    assert(dsu.find(1) == 1);
    assert(dsu.find(10) == 10);
    assert(dsu.check_if_binded(1, 10) == false);
    dsu.merge(1, 10);
    assert(dsu.check_if_binded(1, 10) == true);
}

void test_mst() {
    Graph graph;
    graph.readGraph(IN);
    const auto mst = graph.getSpaingTreePrima();
    mst.writeGraph(OUT_1);
}

void inner_test_mst() {
    // test first
    Graph g1;
    g1.readGraph(IN);
    const auto mst1 = g1.getSpaingTreePrima();
    mst1.writeGraph(OUT_1);
    // test second
    Graph g2;
    g2.readGraph(OUT_1);
    const auto mst2 = g2.getSpaingTreePrima();
    mst2.writeGraph(OUT_2);
}

void test_priority_queue() {
    std::priority_queue<pair<int, int>, std::vector<pair<int, int>>, std::greater<>> queue;
    queue.emplace(3, 2);
    queue.emplace(1, 1);
    queue.emplace(1, 4);
    while (!queue.empty()) {
        const auto item = queue.top();
        std::cout << item.first << " " << item.second << '\n';
        queue.pop();
    }
}
