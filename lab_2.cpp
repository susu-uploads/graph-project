
#define GRAPH_PROJECT_EDGE_H

/**
 * Struct used to describe an edge between vertices with or without weight.
 */
struct Edge {
    int from, to, weight;

    Edge(int u, int v, int length = 1);

    friend bool operator<(const Edge &lhs, const Edge &rhs);

    friend bool operator<=(const Edge &lhs, const Edge &rhs);

    friend bool operator>(const Edge &lhs, const Edge &rhs);

    friend bool operator>=(const Edge &lhs, const Edge &rhs);
};



Edge::Edge(const int u, const int v, const int length) : from(u), to(v), weight(length) {}

bool operator<(const Edge &lhs, const Edge &rhs) {
    return lhs.weight < rhs.weight;
}

bool operator<=(const Edge &lhs, const Edge &rhs) {
    return lhs.weight <= rhs.weight;
}

bool operator>(const Edge &lhs, const Edge &rhs) {
    return lhs.weight > rhs.weight;
}

bool operator>=(const Edge &lhs, const Edge &rhs) {
    return lhs.weight >= rhs.weight;
}

#define GRAPH_PROJECT_NODE_H

#include <map>

/**
 * Struct used to describe node of graph with binded children nodes.
 */
struct Node {
    int name;
    std::map<int, int> children{};

    /**
     * Create node with name.
     * @param name Node name.
     */
    explicit Node(int name);

    /**
     * Bind node with other via path with weight.
     * @param vertice Binded node name.
     * @param weight Path weight.
     */
    void connect(int vertice, int weight = 1);

    /**
     * Re-bind node with other via path with weight.
     * @param vertice Binded node name.
     * @param new_weight Path weight.
     * @return Old weight.
     */
    int rebalance(int vertice, int new_weight);
};



Node::Node(const int name) : name(name) {}

void Node::connect(int vertice, int weight) {
    this->children.insert(std::pair{vertice, weight});
}

int Node::rebalance(const int vertice, const int new_weight) {
    auto pair = children.find(vertice);
    int old_weight = pair->second;
    pair->second = new_weight;
    return old_weight;
}


#define DSU_H


#include <vector>


/**
 * Disjoint Sets Data Structure.
 *
 * A disjoint set data structure (also called union find or merge find set) is a data structure that tracks a set of elements partitioned into a number of disjoint (non-overlapping) subsets.
 * Some situations where disjoint sets can be used are: to find connected components of a graph, Лruskal's algorithm for finding Minimum Spanning Tree etc.
 *
 * "https://en.wikipedia.org/wiki/Disjoint-set_data_structure"
 */
class DSU {
    int size;
    std::vector<int> root, rank;

public:
    /**
     * Create disjoint set of this size.
     * @param size Size of the set.
     */
    explicit DSU(int size);

    /**
     * Operation takes a number and returns the set to which this number belongs to.
     * @param number Element of some set.
     * @return Set to which x belongs to.
     */
    int find(int number);

    /**
     * Operation checks if x and y are from same set or not.
     * @param x Element of some set.
     * @param y Element of some set.
     * @return Are elements in the same set or not.
     */
    bool check_if_binded(int x, int y);

    /**
     * Operation combines two disjoint sets to make a single set.
     * @param x Element of some set.
     * @param y Element of some set.
     */
    void merge(int x, int y);
};




#include <queue>
#include <stdexcept>

DSU::DSU(const int size) : size(size) {
    root = std::vector<int>(size + 1);
    rank = std::vector<int>(size + 1, 1);
    for (int i = 1; i <= size; ++i) {
        root[i] = i;
    }
}

int DSU::find(const int number) {
    if (number < 0 || number > size)
        throw std::invalid_argument("Invalid search number: " + std::to_string(number));
    if (root[number] == number) {
        return number;
    }
    return root[number] = find(root[number]);
}

bool DSU::check_if_binded(const int x, const int y) {
    return find(x) == find(y);
}

void DSU::merge(const int x, const int y) {
    if (x < 0 || x > size)
        throw std::invalid_argument("Invalid search number: " + std::to_string(x));
    if (y < 0 || y > size)
        throw std::invalid_argument("Invalid search number: " + std::to_string(y));
    const int union_x = find(x), union_y = find(y);
    if (union_x != union_y) {
        if (rank[union_x] < rank[union_y]) {
            root[union_x] = union_y;
        } else if (rank[union_x] > rank[union_y]) {
            root[union_y] = union_x;
        } else {
            root[union_x] = union_y;
            ++rank[union_y];
        }
    }
}

#define GRAPH_PROJECT_INNERGRAPH_H

#include <fstream>

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


#define GRAPH_PROJECT_GRAPHASADJLIST_H


#include <vector>
#include <fstream>

/**
 * Used to describe graph as adjustment list.
 */
class GraphAsAdjList final : public InnerGraph {
public:
    std::vector<Node> holder;

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
     * Used to read graph from adjustment matrix.
     * @param s Graph size.
     * @param d Graph directed type. 0 - NOT_DIRECTED. 1 - DIRECTED.
     * @param w Graph weight type. 0 - NOT_WEIGHTED. 1 - WEIGHTED.
     * @param data Data from graph's adjustemnt matrix.
     */
    void load(int s, int d, int w, const std::vector<std::vector<int> > &data);

    /**
     * Used to read graph from edges list.
     * @param s Graph size.
     * @param d Graph directed type. 0 - NOT_DIRECTED. 1 - DIRECTED.
     * @param w Graph weight type. 0 - NOT_WEIGHTED. 1 - WEIGHTED.
     * @param data Data from graph's edges list.
     */
    void load(int s, int d, int w, const std::vector<Edge> &data);

protected:
    /**
     * Used to init graph fields.
     * @param s Graph size.
     * @param d Graph directed type. 0 - NOT_DIRECTED. 1 - DIRECTED.
     * @param w Graph weight type. 0 - NOT_WEIGHTED. 1 - WEIGHTED.
     */
    void init(int s, int d, int w) override;
};



#include <sstream>

using namespace std;

std::vector<int> parseWithoutWeight(const std::string &line) {
    vector<int> data;
    int token;
    istringstream token_stream(line);
    while (token_stream >> token) {
        data.push_back(token);
    }
    return data;
}

std::vector<std::pair<int, int>> parseWithWeight(const std::string &line) {
    vector<pair<int, int>> data;
    int token1;
    int token2;
    istringstream token_stream(line);
    while (token_stream >> token1 >> token2) {
        data.emplace_back(token1, token2);
    }
    return data;
}

void GraphAsAdjList::addEdge(const int from, const int to, const int weight) {
    holder[from].children.insert(pair{to, weight});
}

void GraphAsAdjList::removeEdge(const int from, const int to) {
    holder[from].children.erase(to);
}

int GraphAsAdjList::changeEdge(const int from, const int to, const int newWeight) {
    return holder[from].rebalance(to, newWeight);
}

void GraphAsAdjList::load(std::ifstream &input) {
    int N, D, W;
    input >> N >> D >> W;
    init(N, D, W);
    string line;
    getline(input, line);
    if (weighted == NOT_WEIGHTED) {
        for (int i = 0; i < size; i++) {
            getline(input, line);
            auto data = parseWithoutWeight(line);
            for (const auto vertice : data) {
                addEdge(i, vertice - 1, 1);
            }
        }
    } else if (weighted == WEIGHTED) {
        for (int i = 0; i < size; i++) {
            getline(input, line);
            auto data = parseWithWeight(line);
            for (const auto vertice : data) {
                addEdge(i, vertice.first - 1, vertice.second);
            }
        }
    }
}

void GraphAsAdjList::dump(std::ofstream &output) {
    output << size << '\n';
    output << directed << ' ' << weighted << '\n';
    for (const Node &node : holder) {
        for (const auto edge : node.children) {
            output << edge.first + 1 << ' ';
            if (weighted) {
                output << edge.second << ' ';
            }
        }
        output << '\n';
    }
}

void GraphAsAdjList::load(const int s, const int d, const int w, const std::vector<std::vector<int>> &data) {
    init(s, d, w);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (data[i][j] != 0) {
                addEdge(i, j, data[i][j]);
            }
        }
    }
}

void GraphAsAdjList::load(const int s, const int d, const int w, const std::vector<Edge> &data) {
    init(s, d, w);
    if (directed == NOT_DIRECTED) {
        for (const auto edge : data) {
            addEdge(edge.from, edge.to, edge.weight);
            addEdge(edge.to, edge.from, edge.weight);
        }
    } else if (directed == DIRECTED) {
        for (const auto edge : data) {
            addEdge(edge.from, edge.to, edge.weight);
        }
    }
}

void GraphAsAdjList::init(const int s, const int d, const int w) {
    size = s;
    directed = d;
    weighted = w;
    holder.clear();
    for (int i = 0; i < size; i++) {
        holder.emplace_back(i);
    }
}

#define GRAPH_PROJECT_GRAPHASADJMATRIX_H


#include <vector>
#include <fstream>


/**
 * Used to describe graph as adjustment matrix.
 */
class GraphAsAdjMatrix final : public InnerGraph {
public:
    std::vector<std::vector<int> > holder;

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
     * Used to read graph from edges list.
     * @param s Graph size.
     * @param d Graph directed type. 0 - NOT_DIRECTED. 1 - DIRECTED.
     * @param w Graph weight type. 0 - NOT_WEIGHTED. 1 - WEIGHTED.
     * @param data Data from graph's edges list.
     */
    void load(int s, int d, int w, const std::vector<Edge> &data);

    /**
     * Used to read graph from adjustment list.
     * @param s Graph size.
     * @param d Graph directed type. 0 - NOT_DIRECTED. 1 - DIRECTED.
     * @param w Graph weight type. 0 - NOT_WEIGHTED. 1 - WEIGHTED.
     * @param data Data from graph's adjustemnt list.
     */
    void load(int s, int d, int w, const std::vector<Node> &data);

protected:
    /**
     * Used to init graph fields.
     * @param s Graph size.
     * @param d Graph directed type. 0 - NOT_DIRECTED. 1 - DIRECTED.
     * @param w Graph weight type. 0 - NOT_WEIGHTED. 1 - WEIGHTED.
     */
    void init(int s, int d, int w) override;
};




using namespace std;

void GraphAsAdjMatrix::addEdge(const int from, const int to, const int weight) {
    holder[from][to] = weight;
}

void GraphAsAdjMatrix::removeEdge(const int from, const int to) {
    holder[from][to] = 0;
}

int GraphAsAdjMatrix::changeEdge(const int from, const int to, const int newWeight) {
    int old_weight = holder[from][to];
    holder[from][to] = newWeight;
    return old_weight;
}

void GraphAsAdjMatrix::load(std::ifstream &input) {
    int N, D, W;
    input >> N >> D >> W;
    init(N, D, W);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int weight;
            input >> weight;
            addEdge(i, j, weight);
        }
    }
}

void GraphAsAdjMatrix::dump(std::ofstream &output) {
    output << size << '\n';
    output << directed << ' ' << weighted << '\n';
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            output << holder[i][j];
            if (j != size - 1) {
                output << ' ';
            }
        }
        output << '\n';
    }
}

void GraphAsAdjMatrix::init(const int s, const int d, const int w) {
    size = s;
    directed = d;
    weighted = w;
    holder.clear();
    holder.resize(s, vector<int>(s));
}

void GraphAsAdjMatrix::load(const int s, const int d, const int w, const std::vector<Edge> &data) {
    init(s, d, w);
    if (directed == NOT_DIRECTED) {
        for (const Edge edge : data) {
            addEdge(edge.from, edge.to, edge.weight);
            addEdge(edge.to, edge.from, edge.weight);
        }
    } else if (directed == DIRECTED) {
        for (const Edge edge : data) {
            addEdge(edge.from, edge.to, edge.weight);
        }
    }
}

void GraphAsAdjMatrix::load(const int s, const int d, const int w, const std::vector<Node> &data) {
    init(s, d, w);
    for (const auto &node : data) {
        for (auto connection : node.children) {
            addEdge(node.name, connection.first, connection.second);
        }
    }
}

#define GRAPH_PROJECT_GRAPHASEDGESLIST_H


#include <vector>
#include <fstream>

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



#include <set>

using namespace std;

void GraphAsEdgesList::addEdge(const int from, const int to, const int weight) {
    holder.emplace_back(from, to, weight);
}

void GraphAsEdgesList::removeEdge(const int from, const int to) {
    for (auto edge = holder.begin(); edge != holder.end(); ++edge) {
        if (directed == NOT_DIRECTED) {
            if (edge->from == from && edge->to == to || edge->from == to && edge->to == from) {
                holder.erase(edge);
                return;
            }
        } else if (directed == DIRECTED) {
            if (edge->from == from && edge->to == to) {
                holder.erase(edge);
                return;
            }
        }
    }
}

int GraphAsEdgesList::changeEdge(const int from, const int to, const int newWeight) {
    int old_weight = -1;
    for (auto &edge : holder) {
        if (directed == NOT_DIRECTED) {
            if (edge.from == from && edge.to == to || edge.from == to && edge.to == from) {
                old_weight = edge.weight;
                edge.weight = newWeight;
                return old_weight;
            }
        } else if (directed == DIRECTED) {
            if (edge.from == from && edge.to == to) {
                old_weight = edge.weight;
                edge.weight = newWeight;
                return old_weight;
            }
        }
    }
    return old_weight;
}

void GraphAsEdgesList::load(std::ifstream &input) {
    int N, M, D, W;
    input >> N >> M >> D >> W;
    init(N, D, W);
    if (weighted == NOT_WEIGHTED) {
        int a, b;
        while (M-- > 0) {
            input >> a >> b;
            addEdge(a - 1, b - 1, 1);
        }
    } else if (weighted == WEIGHTED) {
        int a, b, w;
        while (M-- > 0) {
            input >> a >> b >> w;
            addEdge(a - 1, b - 1, w);
        }
    }
}

void GraphAsEdgesList::dump(std::ofstream &output) {
    output << size << ' ' << holder.size() << '\n';
    output << directed << ' ' << weighted << '\n';
    if (weighted == NOT_WEIGHTED) {
        for (Edge edge : holder) {
            output << edge.from + 1 << ' ' << edge.to + 1 << '\n';
        }
    } else if (weighted == WEIGHTED) {
        for (Edge edge : holder) {
            output << edge.from + 1 << ' ' << edge.to + 1 << ' ' << edge.weight << '\n';
        }
    }
}

bool check_if_duplicate(vector<set<int>> &used, const int v, const int w) {
    bool is_duplicate = (used[v].find(w) != used[v].end()) || (used[w].find(v) != used[w].end());
    used[v].insert(w);
    used[w].insert(v);
    return is_duplicate;
}

void GraphAsEdgesList::load(const int s, const int d, const int w, const std::vector<Node> &data) {
    init(s, d, w);
    if (directed == NOT_DIRECTED) {
        vector<set<int>> used(size);
        for (const auto &node : data) {
            for (const auto edge : node.children) {
                if (!check_if_duplicate(used, node.name, edge.first)) {
                    addEdge(node.name, edge.first, edge.second);
                }
            }
        }
    } else if (directed == DIRECTED) {
        for (const auto &node : data) {
            for (const auto edge : node.children) {
                addEdge(node.name, edge.first, edge.second);
            }
        }
    }
}

void GraphAsEdgesList::load(const int s, const int d, const int w, const std::vector<std::vector<int>> &data) {
    init(s, d, w);
    if (directed == NOT_DIRECTED) {
        for (int i = 0; i < size; i++) {
            for (int j = i; j < size; j++) {
                if (data[i][j] != 0) {
                    addEdge(i, j, data[i][j]);
                }
            }
        }
    } else if (directed == DIRECTED) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (data[i][j] != 0) {
                    addEdge(i, j, data[i][j]);
                }
            }
        }
    }
}

void GraphAsEdgesList::init(const int s, const int d, const int w) {
    size = s;
    weighted = w;
    directed = d;
    holder.clear();
}

#define GRAPH_PROJECT_GRAPH_H


#include <string>

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
    int representation;
    InnerGraph *innerGraph;

public:
    /**
     * Initialize graph object.
     */
    Graph();

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



#define MST_H


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



#include <algorithm>
#include <queue>


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

#include <fstream>

#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stdexcept>


using namespace std;

Graph::Graph() : representation(EDGES_LIST) {
    innerGraph = new GraphAsEdgesList;
    innerGraph->size = 0;
    innerGraph->directed = NOT_DIRECTED;
    innerGraph->weighted = WEIGHTED;
}

Graph::Graph(const int size) : representation(EDGES_LIST) {
    innerGraph = new GraphAsEdgesList;
    innerGraph->size = size;
    innerGraph->directed = NOT_DIRECTED;
    innerGraph->weighted = WEIGHTED;
}

void Graph::readGraph(const std::string &fileName) {
    ifstream fileStream{fileName, ios_base::in};
    char inputType;
    fileStream >> inputType;
    if (inputType == ADJUSTMENT_MATRIX_INDICATOR) {
        representation = ADJUSTMENT_MATRIX;
        innerGraph = new GraphAsAdjMatrix;
    } else if (inputType == ADJUSTMENT_LIST_INDICATOR) {
        representation = ADJUSTMENT_LIST;
        innerGraph = new GraphAsAdjList;
    } else if (inputType == EDGES_LIST_INDICATOR) {
        representation = EDGES_LIST;
        innerGraph = new GraphAsEdgesList;
    } else {
        throw invalid_argument("Unrecognizable format: " + to_string(inputType));
    }
    innerGraph->load(fileStream);
}

void Graph::addEdge(const int from, const int to, const int weight) const {
    innerGraph->addEdge(from, to, weight);
}

void Graph::removeEdge(const int from, const int to) const {
    innerGraph->removeEdge(from, to);
}

int Graph::changeEdge(const int from, const int to, const int newWeight) const {
    return innerGraph->changeEdge(from, to, newWeight);
}

void Graph::transformToAdjMatrix() {
    if (representation == ADJUSTMENT_MATRIX) {
        return;
    }
    const auto new_graph = new GraphAsAdjMatrix;
    if (representation == ADJUSTMENT_LIST) {
        const auto adjl_graph = dynamic_cast<GraphAsAdjList *>(innerGraph);
        new_graph->load(adjl_graph->size, adjl_graph->directed, adjl_graph->weighted, adjl_graph->holder);
    } else if (representation == EDGES_LIST) {
        const auto edjl_graph = dynamic_cast<GraphAsEdgesList *>(innerGraph);
        new_graph->load(edjl_graph->size, edjl_graph->directed, edjl_graph->weighted, edjl_graph->holder);
    }
    innerGraph = new_graph;
    representation = ADJUSTMENT_MATRIX;
}

void Graph::transformToAdjList() {
    if (representation == ADJUSTMENT_LIST) {
        return;
    }
    const auto new_graph = new GraphAsAdjList;
    if (representation == ADJUSTMENT_MATRIX) {
        const auto adjm_graph = dynamic_cast<GraphAsAdjMatrix *>(innerGraph);
        new_graph->load(adjm_graph->size, adjm_graph->directed, adjm_graph->weighted, adjm_graph->holder);
    } else if (representation == EDGES_LIST) {
        const auto edjl_graph = dynamic_cast<GraphAsEdgesList *>(innerGraph);
        new_graph->load(edjl_graph->size, edjl_graph->directed, edjl_graph->weighted, edjl_graph->holder);
    }
    innerGraph = new_graph;
    representation = ADJUSTMENT_LIST;
}

void Graph::transformToListOfEdges() {
    if (representation == EDGES_LIST) {
        return;
    }
    const auto new_graph = new GraphAsEdgesList;
    if (representation == ADJUSTMENT_MATRIX) {
        const auto adjm_graph = dynamic_cast<GraphAsAdjMatrix *>(innerGraph);
        new_graph->load(adjm_graph->size, adjm_graph->directed, adjm_graph->weighted, adjm_graph->holder);
    } else if (representation == ADJUSTMENT_LIST) {
        const auto adjl_graph = dynamic_cast<GraphAsAdjList *>(innerGraph);
        new_graph->load(adjl_graph->size, adjl_graph->directed, adjl_graph->weighted, adjl_graph->holder);
    }
    innerGraph = new_graph;
    representation = EDGES_LIST;
}

void Graph::writeGraph(const std::string &fileName) const {
    ofstream fileStream{fileName, ios_base::out};
    if (representation == ADJUSTMENT_MATRIX) {
        fileStream << ADJUSTMENT_MATRIX_INDICATOR << ' ';
    } else if (representation == ADJUSTMENT_LIST) {
        fileStream << ADJUSTMENT_LIST_INDICATOR << ' ';
    } else if (representation == EDGES_LIST) {
        fileStream << EDGES_LIST_INDICATOR << ' ';
    }
    innerGraph->dump(fileStream);
}

Graph Graph::getSpaingTreePrima() {
    this->transformToAdjList();
    const auto representation = dynamic_cast<GraphAsAdjList *>(innerGraph);
    const Graph mst(representation->size);
    make_prima_mst(mst, representation->size, representation->holder);
    return mst;
}

Graph Graph::getSpaingTreeKruscal() {
    this->transformToListOfEdges();
    const auto representation = dynamic_cast<GraphAsEdgesList *>(innerGraph);
    const Graph mst(representation->size);
    make_kruskal_mst(mst, representation->size, representation->holder);
    return mst;
}

Graph Graph::getSpaingTreeBoruvka() {
    this->transformToListOfEdges();
    const auto representation = dynamic_cast<GraphAsEdgesList *>(innerGraph);
    const Graph mst(representation->size);
    make_boruvka_mst(mst, representation->size, representation->holder);
    return mst;
}

int main()
{
    Graph g;
    g.readGraph("input.txt");
    //Graph gg=g.getSpaingTreeBoruvka();
    Graph gg = g.getSpaingTreeKruscal();
    // Graph gg=g.getSpaingTreePrima();
    gg.transformToAdjList();
    gg.writeGraph("output.txt");
    return 0;
}
