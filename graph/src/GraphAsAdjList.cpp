//
// Created by mick on 2/26/24.
//

#include <sstream>
#include <Edge.h>
#include "GraphAsAdjList.h"

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
    std::string line;
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
