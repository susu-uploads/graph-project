#include <iostream>
#include "graph/include/Graph.h"

using namespace std;

int main() {
    Graph g;
    g.readGraph("/home/mick/CLionProjects/graph-project/res/input_1e3_1e5.txt");
    g.writeGraph("/home/mick/CLionProjects/graph-project/res/out");
    return 0;
}
