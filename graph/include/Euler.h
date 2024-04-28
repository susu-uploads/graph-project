//
// Created by mick on 29.04.24.

#ifndef EULER_H
#define EULER_H
#include <vector>

#include "Node.h"

#endif //EULER_H

/**
 * Tries to find the best starting point for Euler path/cycle.
 * @param vertices Graph vertices.
 * @return Node index and what type it is - Euler path 0 or Euler cycle 1. Throws exception otherwise.
 */
std::pair<int, bool> find_vertice(const std::vector<Node> &vertices);
