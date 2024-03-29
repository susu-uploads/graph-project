#include <cassert>
#include <iostream>
#include <queue>

#include "graph/include/Graph.h"
#include "util/include/DSU.h"

using namespace std;

#define IN "/home/mick/CLionProjects/graph-project/res/in"
#define OUT_1 "/home/mick/CLionProjects/graph-project/res/out_1"
#define OUT_2 "/home/mick/CLionProjects/graph-project/res/out_2"
#define OUT_3 "/home/mick/CLionProjects/graph-project/res/out_3"

void test_with_my_graph();

void test_with_given_graph();

void test_dsu();

void test_mst();

void test_priority_queue();

int main() {
    test_mst();
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

// 1-(29)-2
// 1-(30)-3
// 1-(1)-4
// 1-(4)-5
// 2-(23)-3
// 3-(28)-4
// 4-(13)-5
// 2-(10)-6
// 2-(15)-7
// 3-(12)-7
// 3-(15)-8
// 4-(24)-8
// 4-(25)-9
// 5-(1)-9
// 6-(11)-3
// 7-(19)-4
// 8-(8)-5
// 9-(20)-8
// 8-(21)-7
// 7-(25)-6
// 6-(27)-10
// 7-(28)-10
// 9-(19)-11
// 8-(20)-11
// 10-(18)-11
