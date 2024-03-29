//
// Created by mick on 29.03.24.
//

#ifndef MST_H
#define MST_H
#include "Graph.h"


/**
     * Internal Prima's MST construction algorithm.
     * @param mst MST graph pointer.
     * @param size Size of the initial graph.
     * @param data Data representation as adjustment list.
     * @throws illegal_argument_exception When MST tree cannot be constructed.
     */
void make_prima_mst(const Graph &mst, int size, std::vector<Node> &data);

/**
  * Internal Kruskal's MST construction algorithm.
  * @param mst MST graph pointer.
  * @param size Size of the initial graph.
  * @param data Data representation as edges list.
  * @throws illegal_argument_exception When MST tree cannot be constructed.
  */
void make_kruskal_mst(const Graph &mst, int size, std::vector<Edge> &data);

/**
  * Internal Boruvka's MST construction algorithm.
  * @param mst MST graph pointer.
  * @param size Size of the initial graph.
  * @param data Data representation as edges list.
  * @throws illegal_argument_exception When MST tree cannot be constructed.
  */
void make_boruvka_mst(const Graph &mst, int size, std::vector<Edge> &data);

#endif //MST_H
