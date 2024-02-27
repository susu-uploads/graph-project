
#ifndef GRAPH_PROJECT_EDGE_H
#define GRAPH_PROJECT_EDGE_H

struct Edge {
    int from, to, weight;

    Edge(int v, int w, int length = 1);
};

#endif //GRAPH_PROJECT_EDGE_H


Edge::Edge(int v, int w, int length) : from(v), to(w), weight(length) {}


#ifndef GRAPH_PROJECT_NODE_H
#define GRAPH_PROJECT_NODE_H

#include <map>

struct Node {
    int name;
    std::map<int, int> children{};

    explicit Node(int name);

    void connect(int vertice, int weight = 1);

    int rebalance(int vertice, int new_weight);
};

#endif //GRAPH_PROJECT_NODE_H


Node::Node(int name) : name(name) {}

void Node::connect(int vertice, int weight) {
    this->children.insert(std::pair<int, int>{vertice, weight});
}

int Node::rebalance(int vertice, int new_weight) {
    auto pair = children.find(vertice);
    int old_weight = pair->second;
    pair->second = new_weight;
    return old_weight;
}


#ifndef GRAPH_PROJECT_INNERGRAPH_H
#define GRAPH_PROJECT_INNERGRAPH_H

#include <fstream>

#define NOT_DIRECTED 0
#define DIRECTED 1
#define NOT_WEIGHTED 0
#define WEIGHTED 1

class InnerGraph {
public:
    int size{};
    int weighted{};
    int directed{};

    virtual void init(int s, int d, int w) {}

    virtual void addEdge(int from, int to, int weight) {}

    virtual void removeEdge(int from, int to) {}

    virtual int changeEdge(int from, int to, int newWeight) {
        return -1;
    }

    virtual void load(std::ifstream &input) {}

    virtual void dump(std::ofstream &output) {}
};

#endif //GRAPH_PROJECT_INNERGRAPH_H

#ifndef GRAPH_PROJECT_GRAPHASADJLIST_H
#define GRAPH_PROJECT_GRAPHASADJLIST_H


#include <vector>

class GraphAsAdjList : public InnerGraph {
public:
    std::vector<Node> holder;

    void init(int s, int d, int w) override;

    void addEdge(int from, int to, int weight) override;

    void removeEdge(int from, int to) override;

    int changeEdge(int from, int to, int newWeight) override;

    void load(std::ifstream &input) override;

    void dump(std::ofstream &output) override;

    void load(int s, int d, int w, const std::vector<std::vector<int>> &data);

    void load(int s, int d, int w, const std::vector<Edge> &data);
};


#endif //GRAPH_PROJECT_GRAPHASADJLIST_H

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

void GraphAsAdjList::addEdge(int from, int to, int weight) {
    holder[from].children.insert(pair<int, int>{to, weight});
}

void GraphAsAdjList::removeEdge(int from, int to) {
    holder[from].children.erase(to);
}

int GraphAsAdjList::changeEdge(int from, int to, int newWeight) {
    return holder[from].rebalance(to, newWeight);
}

void GraphAsAdjList::load(std::ifstream &input) {
    // Init fields
    int N, D, W;
    input >> N >> D >> W;
    init(N, D, W);
    std::string line;
    getline(input, line);
    // Read data
    if (weighted == NOT_WEIGHTED) {
        for (int i = 0; i < size; i++) {
            getline(input, line);
            auto data = parseWithoutWeight(line);
            for (int vertice : data) {
                addEdge(i, vertice - 1, 1);
            }
        }
    } else if (weighted == WEIGHTED) {
        for (int i = 0; i < size; i++) {
            getline(input, line);
            auto data = parseWithWeight(line);
            for (std::pair<int, int> vertice : data) {
                addEdge(i, vertice.first - 1, vertice.second);
            }
        }
    }
}

void GraphAsAdjList::dump(std::ofstream &output) {
    output << size << '\n';
    output << directed << ' ' << weighted << '\n';
    for (const Node &node : holder) {
        for (std::pair<int, int> edge : node.children) {
            output << edge.first + 1 << ' ';
            if (weighted) {
                output << edge.second << ' ';
            }
        }
        output << '\n';
    }
}

void GraphAsAdjList::load(int s, int d, int w, const std::vector<std::vector<int>> &data) {
    init(s, d, w);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            addEdge(i, j, data[i][j]);
        }
    }
}

void GraphAsAdjList::load(int s, int d, int w, const std::vector<Edge> &data) {
    init(s, d, w);
    if (directed == NOT_DIRECTED) {
        for (Edge edge : data) {
            addEdge(edge.from, edge.to, edge.weight);
            addEdge(edge.to, edge.from, edge.weight);
        }
    } else if (directed == DIRECTED) {
        for (Edge edge : data) {
            addEdge(edge.from, edge.to, edge.weight);
        }
    }
}

void GraphAsAdjList::init(int s, int d, int w) {
    size = s;
    directed = d;
    weighted = w;
    holder.clear();
    for (int i = 0; i < size; i++) {
        holder.emplace_back(i);
    }
}

#ifndef GRAPH_PROJECT_GRAPHASADJMATRIX_H
#define GRAPH_PROJECT_GRAPHASADJMATRIX_H



class GraphAsAdjMatrix : public InnerGraph {
public:
    std::vector<std::vector<int>> holder;

    void init(int s, int d, int w) override;

    void addEdge(int from, int to, int weight) override;

    void removeEdge(int from, int to) override;

    int changeEdge(int from, int to, int newWeight) override;

    void load(std::ifstream &input) override;

    void dump(std::ofstream &output) override;

    void load(int s, int d, int w, const std::vector<Edge> &data);

    void load(int s, int d, int w, const std::vector<Node> &data);
};


#endif //GRAPH_PROJECT_GRAPHASADJMATRIX_H


using namespace std;

void GraphAsAdjMatrix::addEdge(int from, int to, int weight) {
    holder[from][to] = weight;
}

void GraphAsAdjMatrix::removeEdge(int from, int to) {
    holder[from][to] = 0;
}

int GraphAsAdjMatrix::changeEdge(int from, int to, int newWeight) {
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

void GraphAsAdjMatrix::init(int s, int d, int w) {
    size = s;
    directed = d;
    weighted = w;
    holder.clear();
    holder.resize(s, vector<int>(s));
}

void GraphAsAdjMatrix::load(int s, int d, int w, const std::vector<Edge> &data) {
    init(s, d, w);
    if (directed == NOT_DIRECTED) {
        for (Edge edge : data) {
            addEdge(edge.from, edge.to, edge.weight);
            addEdge(edge.to, edge.from, edge.weight);
        }
    } else if (directed == DIRECTED) {
        for (Edge edge : data) {
            addEdge(edge.from, edge.to, edge.weight);
        }
    }
}

void GraphAsAdjMatrix::load(int s, int d, int w, const std::vector<Node> &data) {
    init(s, d, w);
    for (const auto &node : data) {
        for (auto connection : node.children) {
            addEdge(node.name, connection.first, connection.second);
        }
    }
}

#ifndef GRAPH_PROJECT_GRAPHASEDGESLIST_H
#define GRAPH_PROJECT_GRAPHASEDGESLIST_H



class GraphAsEdgesList : public InnerGraph {
public:
    std::vector<Edge> holder;

    void init(int s, int d, int w) override;

    void addEdge(int from, int to, int weight) override;

    void removeEdge(int from, int to) override;

    int changeEdge(int from, int to, int newWeight) override;

    void load(std::ifstream &input) override;

    void dump(std::ofstream &output) override;

    void load(int s, int d, int w, const std::vector<Node> &data);

    void load(int s, int d, int w, const std::vector<std::vector<int>> &data);
};


#endif //GRAPH_PROJECT_GRAPHASEDGESLIST_H

#include <set>

using namespace std;

void GraphAsEdgesList::addEdge(int from, int to, int weight) {
    holder.emplace_back(from, to, weight);
}

void GraphAsEdgesList::removeEdge(int from, int to) {
    for (auto edge = holder.begin(); edge != holder.end(); edge++) {
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

int GraphAsEdgesList::changeEdge(int from, int to, int newWeight) {
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

bool check_if_duplicate(vector<set<int>> &used, int v, int w) {
    bool is_duplicate = (used[v].find(w) != used[v].end()) || (used[w].find(v) != used[w].end());
    used[v].insert(w);
    used[w].insert(v);
    return is_duplicate;
}

void GraphAsEdgesList::load(int s, int d, int w, const std::vector<Node> &data) {
    init(s, d, w);
    if (directed == NOT_DIRECTED) {
        vector<set<int>> used(size);
        for (const auto &node : data) {
            for (auto edge : node.children) {
                if (!check_if_duplicate(used, node.name, edge.first)) {
                    addEdge(node.name, edge.first, edge.second);
                }
            }
        }
    } else if (directed == DIRECTED) {
        for (const auto &node : data) {
            for (auto edge : node.children) {
                addEdge(node.name, edge.first, edge.second);
            }
        }
    }
}

void GraphAsEdgesList::load(int s, int d, int w, const std::vector<std::vector<int>> &data) {
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

void GraphAsEdgesList::init(int s, int d, int w) {
    size = s;
    weighted = w;
    directed = d;
    holder.clear();
}

#ifndef GRAPH_PROJECT_GRAPH_H
#define GRAPH_PROJECT_GRAPH_H


#include <string>

class Graph {
private:
    int representation{};
    int viewer{};
    GraphAsAdjMatrix c;
    GraphAsAdjList l;
    GraphAsEdgesList e;
public:
    void readGraph(const std::string &n);

    void addEdge(int from, int to, int weight);

    void removeEdge(int from, int to);

    int changeEdge(int from, int to, int newWeight);

    void transformToAdjList();

    void transformToAdjMatrix();

    void transformToListOfEdges();

    void writeGraph(const std::string &fileName);
};


#endif //GRAPH_PROJECT_GRAPH_H

#include <functional>

#define ADJUSTMENT_MATRIX 0
#define ADJUSTMENT_LIST 1
#define EDGES_LIST 2

using namespace std;

void Graph::readGraph(const std::string &n) {
    // Open stream
    ifstream fileStream{n, ios_base::in};
    // Discovering what input pattern is
    char inputType;
    fileStream >> inputType;
    if (inputType == 'C') {
        representation = ADJUSTMENT_MATRIX;
        viewer = ADJUSTMENT_MATRIX;
        c.load(fileStream);
    } else if (inputType == 'L') {
        representation = ADJUSTMENT_LIST;
        viewer = ADJUSTMENT_LIST;
        l.load(fileStream);
    } else if (inputType == 'E') {
        representation = EDGES_LIST;
        viewer = EDGES_LIST;
        e.load(fileStream);
    } else {
        throw invalid_argument("Unrecognizable format: " + to_string(inputType));
    }
}

void Graph::addEdge(int from, int to, int weight) {
    if (representation == ADJUSTMENT_MATRIX) {
        c.addEdge(from, to, weight);
    } else if (representation == ADJUSTMENT_LIST) {
        l.addEdge(from, to, weight);
    } else if (representation == EDGES_LIST) {
        e.addEdge(from, to, weight);
    } else {
        throw invalid_argument("Unrecognizable format: " + to_string(representation));
    }
}

void Graph::removeEdge(int from, int to) {
    if (representation == ADJUSTMENT_MATRIX) {
        c.removeEdge(from, to);
    } else if (representation == ADJUSTMENT_LIST) {
        l.removeEdge(from, to);
    } else if (representation == EDGES_LIST) {
        e.removeEdge(from, to);
    } else {
        throw invalid_argument("Unrecognizable format: " + to_string(representation));
    }
}

int Graph::changeEdge(int from, int to, int newWeight) {
    if (representation == ADJUSTMENT_MATRIX) {
        return c.changeEdge(from, to, newWeight);
    } else if (representation == ADJUSTMENT_LIST) {
        return l.changeEdge(from, to, newWeight);
    } else if (representation == EDGES_LIST) {
        return e.changeEdge(from, to, newWeight);
    } else {
        throw invalid_argument("Unrecognizable format: " + to_string(representation));
    }
}

void Graph::transformToAdjMatrix() {
    viewer = ADJUSTMENT_MATRIX;
}

void Graph::transformToAdjList() {
    viewer = ADJUSTMENT_LIST;
}

void Graph::transformToListOfEdges() {
    viewer = EDGES_LIST;
}

void Graph::writeGraph(const std::string &fileName) {
    ofstream fileStream{fileName, ios_base::out};
    if (viewer == ADJUSTMENT_MATRIX) {
        fileStream << 'C' << ' ';
        if (representation == ADJUSTMENT_LIST) {
            c.load(l.size, l.directed, l.weighted, l.holder);
            c.dump(fileStream);
        } else if (representation == EDGES_LIST) {
            c.load(e.size, e.directed, e.weighted, e.holder);
            c.dump(fileStream);
        } else {
            c.dump(fileStream);
        }
        representation = ADJUSTMENT_MATRIX;
    } else if (viewer == ADJUSTMENT_LIST) {
        fileStream << 'L' << ' ';
        if (representation == ADJUSTMENT_MATRIX) {
            l.load(c.size, c.directed, c.weighted, c.holder);
            l.dump(fileStream);
        } else if (representation == EDGES_LIST) {
            l.load(e.size, e.directed, e.weighted, e.holder);
            l.dump(fileStream);
        } else {
            l.dump(fileStream);
        }
        representation = ADJUSTMENT_LIST;
    } else if (viewer == EDGES_LIST) {
        fileStream << 'E' << ' ';
        if (representation == ADJUSTMENT_MATRIX) {
            e.load(c.size, c.directed, c.weighted, c.holder);
            e.dump(fileStream);
        } else if (representation == ADJUSTMENT_LIST) {
            e.load(l.size, l.directed, l.weighted, l.holder);
            e.dump(fileStream);
        } else {
            e.dump(fileStream);
        }
        representation = EDGES_LIST;
    } else {
        throw invalid_argument("Unrecognizable format: " + to_string(representation));
    }
}