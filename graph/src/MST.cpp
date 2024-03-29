//
// Created by mick on 29.03.24.
//

#include "../include/MST.h"

#include <algorithm>
#include <queue>

#include "DSU.h"

using namespace std;

void make_prima_mst(const Graph &mst, const int size, std::vector<Node> &data) {
    // setup
    int accessed_nodes_counter = 0;
    vector used_vertices(size, false);
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int> >, greater<> > queue;
    // [WEIGHT, FROM, TO]

    // init
    queue.emplace(0, 0, 0);
    used_vertices[0] = true;

    // algorithm
    while (!queue.empty()) {
        const auto [curr_weight, curr_from, curr_to] = queue.top();
        queue.pop();

        // add edge to new vertice if it wasn't used
        if (used_vertices[curr_from] && !used_vertices[curr_to]) {
            mst.addEdge(curr_from, curr_to, curr_weight);
            accessed_nodes_counter++;
            used_vertices[curr_to] = true;
        }

        // access new edges from vertice
        for (const auto [name, weight]: data[curr_to].children) {
            if (!used_vertices[name]) {
                queue.emplace(weight, curr_to, name);
            }
        }
    }

    // validate
    if (accessed_nodes_counter != size - 1) {
        throw logic_error("Cannot construct MST!");
    }
}

void make_kruskal_mst(const Graph &mst, const int size, std::vector<Edge> &data) {
    // setup
    int accessed_nodes_counter = 0;
    vector<Edge> sorted_edges = data;
    DSU dsu(size);

    // init
    sort(sorted_edges.begin(), sorted_edges.end());

    // algorithm
    for (auto const edge: sorted_edges) {
        if (!dsu.check_if_binded(edge.from, edge.to)) {
            dsu.merge(edge.from, edge.to);
            mst.addEdge(edge.from, edge.to, edge.weight);
            accessed_nodes_counter++;
        }
    }

    // validate
    if (accessed_nodes_counter != size - 1) {
        throw logic_error("Cannot construct MST!");
    }
}

void make_boruvka_mst(const Graph &mst, const int size, std::vector<Edge> &data) {
    // setup
    DSU dsu(size);
    vector<int> rank(size);
    vector cheapest(size, Edge(0, 0, -1));
    // An array to store index of the cheapest edge of  subset. It store [u,v,w] for each component

    // setup
    int numTrees = size;

    // algorithm
    // Keep combining components (or sets) until all components are not combined into single MST
    while (numTrees > 1) {
        // Traverse through all edges and update cheapest of every component
        for (const auto [from, to, weight]: data) {
            const int u_comp = dsu.find(from), v_comp = dsu.find(to);
            // If two corners of current edge belong to same set, ignore current edge.
            // Else check if current edge is closer to previous cheapest edges of u_comp and v_compю
            if (!dsu.check_if_binded(from, to)) {
                if (cheapest[u_comp].weight == -1 || cheapest[u_comp].weight > weight) {
                    cheapest[u_comp] = Edge{from, to, weight};
                }
                if (cheapest[v_comp].weight == -1 || cheapest[v_comp].weight > weight) {
                    cheapest[v_comp] = Edge{from, to, weight};
                }
            }
        }

        // Consider the above picked cheapest edges and add them to MST
        for (int node = 0; node < size; node++) {
            // Check if cheapest for current set exists
            if (cheapest[node].weight != -1) {
                const auto [from, to, weight] = cheapest[node];
                if (!dsu.check_if_binded(from, to)) {
                    dsu.merge(from, to);
                    mst.addEdge(from, to, weight);
                    numTrees--;
                }
            }
        }

        // reset cheapest array
        for (int node = 0; node < size; node++) {
            cheapest[node].weight = -1;
        }
    }
}
