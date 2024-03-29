//
// Created by mick on 2/26/24.
//

#include "GraphAsEdgesList.h"
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
