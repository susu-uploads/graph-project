//
// Created by mick on 29.04.24.
//

#include "../include/MST.h"
#include "Euler.h"

#include <cstring>
#include <functional>
#include <iostream>


/**
 * Util dfs function used to count reachable vertices from node.
 * @param vertices Graph vertices as adjustment list.
 * @param vertice Start vertice.
 * @param used Processed vertices.
 * @param validate Lamda function used to validate edge (in order to not delete in-place edges).
 * @return Number of reachable vertices from start vertice.
 */
int dfs(const std::vector<Node> &vertices, int vertice, bool used[], const std::function<bool(int u, int v)> &validate);

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
        return std::pair{start_v.front(), false};
    }
    throw std::invalid_argument("Unable to detect any Euler path/cycle!");
}

bool is_next_edge_valid(const std::vector<Node> &vertices, const int u, const int v, const int directed) {
    // NOT ADJUSTMENT
    if (vertices[u].children.find(v) == vertices[u].children.end()) {
        return false;
    }

    // SINGLE
    if (vertices[u].children.find(v) != vertices[u].children.end() && vertices[u].children.size() == 1) {
        return true;
    }

    // NOT REMOVING COUNTER
    auto not_removed_validator = [&](int, int) -> bool {
        return true;
    };
    const int count_1 = count_reachable_vertices(vertices, u, not_removed_validator);

    // REMOVING COUNTER
    auto removed_validator = [&](const int a, const int b) -> bool {
        if (directed == NOT_DIRECTED) {
            // std::cout << "a: " << a << " b: " << b << " u: " << u << " v: " << v << std::endl;
            return !((a == u && b == v) || (a == v && b == u));
        }
        return a != u && b != v;
    };
    const int count_2 = count_reachable_vertices(vertices, u, removed_validator);
    return count_1 <= count_2;
}

int count_reachable_vertices(const std::vector<Node> &vertices, const int vertice,
                             const std::function<bool(int u, int v)> &validate) {
    bool used[vertices.size()];
    memset(used, false, vertices.size());
    return dfs(vertices, vertice, used, validate);
}

std::vector<int> find_euler_tour_fluery(std::vector<Node> &vertices, const int is_directed) {
    auto path = std::vector<int>();
    auto [current, isCycle] = find_vertice(vertices);
    while (current != -1) {
        path.push_back(current);
        bool found = false;
        for (auto [node, weight] : vertices[current].children) {
            if (is_next_edge_valid(vertices, current, node, is_directed)) {
                vertices[current].children.erase(node);
                if (!is_directed) {
                    vertices[node].children.erase(current);
                }
                current = node;
                found = true;
                break;
            }
        }
        if (!found) {
            current = -1;
        }
    }

    return path;
}

int dfs(const std::vector<Node> &vertices, const int vertice, bool used[],
        const std::function<bool(int u, int v)> &validate) {
    used[vertice] = true;
    int reached = 1;
    for (const auto [node, weight]: vertices[vertice].children) {
        if (!used[node] && validate(vertice, node)) {
            reached += dfs(vertices, node, used, validate);
        }
    }
    return reached;
}
