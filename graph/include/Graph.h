//
// Created by mick on 12.02.2024.

#ifndef GRAPH_PROJECT_GRAPH_H
#define GRAPH_PROJECT_GRAPH_H


#include <string>
#include "GraphAsAdjList.h"
#include "GraphAsAdjMatrix.h"
#include "GraphAsEdgesList.h"

#define ADJUSTMENT_MATRIX_INDICATOR 'C'
#define ADJUSTMENT_LIST_INDICATOR 'L'
#define EDGES_LIST_INDICATOR 'E'

#define ADJUSTMENT_MATRIX 0
#define ADJUSTMENT_LIST 1
#define EDGES_LIST 2

/**
 * Main class used to describe Graph as is.
 */
class Graph {
    int representation{};
    InnerGraph *innerGraph = nullptr;

public:
    /**
     * Initialize graph object.
     */
    Graph() = default;

    /**
     * Create graph object as edges list.
     * @param size Size of the graph.
     */
    explicit Graph(int size);

    /**
     * Used to read graph from file.
     * @param fileName File name.
     */
    void readGraph(const std::string &fileName);

    /**
     * Used to add edge into graph.
     * @param from Start vertice [id].
     * @param to End vertice [id].
     * @param weight Weight of the edge.
     */
    void addEdge(int from, int to, int weight) const;

    /**
     * Used to remove edge from the graph.
     * @param from Start vertice [id].
     * @param to End vertice [id].
     */
    void removeEdge(int from, int to) const;

    /**
     * Used to change edge weight, if exist. If not exists - throws exception.
     * @param from Start vertice [id].
     * @param to End vertice [id].
     * @param newWeight New weight of the edge.
     */
    int changeEdge(int from, int to, int newWeight) const;

    /**
     * Used to convert current graph representation into ADJUSTMENT_LIST.
     */
    void transformToAdjList();

    /**
     * Used to convert current graph representation into ADJUSTMENT_MATRIX.
     */
    void transformToAdjMatrix();

    /**
     * Used to convert current graph representation into EDGES_LIST.
     */
    void transformToListOfEdges();

    /**
       * Used to write graph into file.
       * @param fileName File name.
       */
    void writeGraph(const std::string &fileName) const;

    /**
     * Calculate MST using Prima's algorithm.
     * @return MST graph.
     */
    Graph getSpaingTreePrima();

    /**
     * Calculate MST using Kruskal's algorithm.
     * @return MST graph.
     */
    Graph getSpaingTreeKruscal();

    /**
     * Calculate MST using Boruvka's algorithm.
     * @return MST graph.
     */
    Graph getSpaingTreeBoruvka();
};


#endif //GRAPH_PROJECT_GRAPH_H
