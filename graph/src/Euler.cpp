//
// Created by mick on 29.04.24.
//

#include "../include/MST.h"
#include "Euler.h"

#include <cstring>
#include <functional>


std::pair<int, bool> find_vertice(const std::vector<Node> &vertices) {
    // Setup
    auto deg_v = std::vector<int>(vertices.size());
    for (const auto &node: vertices) {
        deg_v[node.name] = static_cast<int>(node.children.size());
    }

    // Calculating
    int odd_counter = 0;
    auto start_v = std::vector<int>();
    for (int i = 0; i < deg_v.size(); i++) {
        if (deg_v[i] % 2 == 1) {
            odd_counter += 1;
            start_v.push_back(i);
        }
    }

    // Return
    if (odd_counter == 0) {
        return std::pair{0, true};
    }
    if (odd_counter == 2) {
        return std::pair{start_v.front() + 1, false};
    }
    throw std::invalid_argument("Unable to detect any Euler path/cycle!");
}

bool is_next_edge_valid(const std::vector<Node> &vertices, const int u, const int v, const int directed) {
    // if there's no edge between vertices
    if (vertices[u].children.find(v) == vertices[u].children.end()) {
        return false;
    }
    // The edge u-v is valid in one of the following two cases:

    // 1) If v is the only adjacent vertex of u
    if (vertices[u].children.find(v) != vertices[u].children.end() && vertices[u].children.size() == 1) {
        return true;
    }
    // 2) If there are multiple adjacents, then u-v is not a
    // bridge Do following steps to check if u-v is a bridge

    // 2.a) count of vertices reachable from u
    auto not_removed_validator = [&](int a, int b) -> bool {
        return true;
    };
    const int count_1 = count_reachable_vertices(vertices, u, not_removed_validator);

    // 2.b) Remove edge (u, v) and after removing the edge,
    // count vertices reachable from u
    auto removed_validator = [&](int a, int b) -> bool {
        if (directed == NOT_DIRECTED) {
            return (a != u && b != v) || (a != v && b != u);
        }
        return a != u && b != v;
    };
    const int count_2 = count_reachable_vertices(vertices, u, removed_validator);

    // 2.d) If count1 is greater, then edge (u, v) is a
    // bridge
    return count_1 <= count_2;
}

int dfs(const std::vector<Node> &vertices, const int vertice, bool used[], const std::function<bool(int u, int v)> &validate) {
    used[vertice] = true;
    int reached = 1;
    for (const auto [node, weight]: vertices[vertice].children) {
        if (!used[node] && validate(vertice, node)) {
            reached += dfs(vertices, node, used, validate);
        }
    }
    return reached;
}

int count_reachable_vertices(const std::vector<Node> &vertices, const int vertice, const std::function<bool(int u, int v)> &validate) {
    bool used[vertices.size()];
    memset(used, false, vertices.size());
    return dfs(vertices, vertice, used, validate);
}
