//
// Created by mick on 2/27/24.

#ifndef GRAPH_PROJECT_INNERGRAPH_H
#define GRAPH_PROJECT_INNERGRAPH_H

#define NOT_DIRECTED 0
#define DIRECTED 1
#define NOT_WEIGHTED 0
#define WEIGHTED 1

/**
 * Utility class used to make derived classes of different graph representation types.
 */
class InnerGraph {
public:
    int size{};
    int weighted{};
    int directed{};

    /**
     * Used to add edge into graph.
     * @param from Start vertice [id].
     * @param to End vertice [id].
     * @param weight Weight of the edge.
     */
    virtual void addEdge(int from, int to, int weight) {
    }

    /**
     * Used to remove edge from the graph.
     * @param from Start vertice [id].
     * @param to End vertice [id].
     */
    virtual void removeEdge(int from, int to) {
    }

    /**
     * Used to change edge weight, if exist. If not exists - throws exception.
     * @param from Start vertice [id].
     * @param to End vertice [id].
     * @param newWeight New weight of the edge.
     */
    virtual int changeEdge(int from, int to, int newWeight) {
    }

    /**
     * Used to read graph from filestream.
     * @param input File name.
     */
    virtual void load(std::ifstream &input) {
    }

    /**
       * Used to write graph into filestream.
       * @param output File name.
       */
    virtual void dump(std::ofstream &output) {
    }

    /**
     * Default destructor.
     */
    virtual ~InnerGraph() = default;

protected:
    /**
     * Used to init graph fields.
     * @param s Graph size.
     * @param d Graph directed type. 0 - NOT_DIRECTED. 1 - DIRECTED.
     * @param w Graph weight type. 0 - NOT_WEIGHTED. 1 - WEIGHTED.
     */
    virtual void init(int s, int d, int w) {
    }
};

#endif //GRAPH_PROJECT_INNERGRAPH_H
