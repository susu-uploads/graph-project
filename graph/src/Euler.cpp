//
// Created by mick on 29.04.24.
//

#include "../include/MST.h"

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
