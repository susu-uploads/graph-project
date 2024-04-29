//
// Created by mick on 29.04.24.

#ifndef EULER_H
#define EULER_H
#include <functional>
#include <vector>

#include "Node.h"

#endif //EULER_H

/**
 * Tries to find the best starting point for Euler path/cycle.
 * @param vertices Graph vertices.
 * @return Node index and what type it is - Euler path 0 or Euler cycle 1. Throws exception otherwise.
 */
std::pair<int, bool> find_vertice(const std::vector<Node> &vertices);

/**
 * Checks if this edge a bridge in the graph.
 * @param vertices Graph vertices as adjustment list.
 * @param u Vertice from.
 * @param v Vertice to.
 * @param directed 0 - NOT DIRECTED, 1 - DIRECTED.
 * @return Is this edge a bridge.
 */
bool is_next_edge_valid(const std::vector<Node> &vertices, int u, int v, int directed);

/**
 * Calculates number of reachable vertices from this vertice.
 * @param vertices Graph vertices as adjustment list.
 * @param vertice Start vertice.
 * @param validate Is this edge can be processed.
 * @return Count of reachable vertices.
 */
int count_reachable_vertices(const std::vector<Node> &vertices, int vertice, const std::function<bool(int u, int v)> &validate);

/**
 * Calculates Euler path/cycle using Fluery's algorithm.
 * @param vertices Graph vertices as adjustment list. WILL BE MODIFIED!
 * @param is_directed 0 - NOT_DIRECTED, 1 - DIRECTED.
 * @return Euler path/cycle if exists.
 */
std::vector<int> find_euler_tour_fluery(std::vector<Node> &vertices, int is_directed);