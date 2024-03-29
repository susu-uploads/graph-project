//
// Created by mick on 2/26/24.

#ifndef GRAPH_PROJECT_GRAPHASEDGESLIST_H
#define GRAPH_PROJECT_GRAPHASEDGESLIST_H


#include <vector>
#include <fstream>
#include "Edge.h"
#include "Node.h"
#include "InnerGraph.h"

/**
 * Used to describe graph as edges list.
 */
class GraphAsEdgesList final : public InnerGraph {
public:
    std::vector<Edge> holder;

    /**
     * Used to add edge into graph.
     * @param from Start vertice [id].
     * @param to End vertice [id].
     * @param weight Weight of the edge.
     */
    void addEdge(int from, int to, int weight) override;

    /**
     * Used to remove edge from the graph.
     * @param from Start vertice [id].
     * @param to End vertice [id].
     */
    void removeEdge(int from, int to) override;

    /**
     * Used to change edge weight, if exist. If not exists - throws exception.
     * @param from Start vertice [id].
     * @param to End vertice [id].
     * @param newWeight New weight of the edge.
     */
    int changeEdge(int from, int to, int newWeight) override;

    /**
     * Used to read graph from filestream.
     * @param input File name.
     */
    void load(std::ifstream &input) override;

    /**
     * Used to write graph into filestream.
     * @param output File name.
     */
    void dump(std::ofstream &output) override;

    /**
     * Used to read graph from adjustment list.
     * @param s Graph size.
     * @param d Graph directed type. 0 - NOT_DIRECTED. 1 - DIRECTED.
     * @param w Graph weight type. 0 - NOT_WEIGHTED. 1 - WEIGHTED.
     * @param data Data from graph's adjustemnt list.
     */
    void load(int s, int d, int w, const std::vector<Node> &data);

    /**
     * Used to read graph from adjustment matrix.
     * @param s Graph size.
     * @param d Graph directed type. 0 - NOT_DIRECTED. 1 - DIRECTED.
     * @param w Graph weight type. 0 - NOT_WEIGHTED. 1 - WEIGHTED.
     * @param data Data from graph's adjustemnt matrix.
     */
    void load(int s, int d, int w, const std::vector<std::vector<int> > &data);

protected:
    /**
     * Used to init graph fields.
     * @param s Graph size.
     * @param d Graph directed type. 0 - NOT_DIRECTED. 1 - DIRECTED.
     * @param w Graph weight type. 0 - NOT_WEIGHTED. 1 - WEIGHTED.
     */
    void init(int s, int d, int w) override;
};


#endif //GRAPH_PROJECT_GRAPHASEDGESLIST_H
