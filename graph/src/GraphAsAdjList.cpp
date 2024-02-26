//
// Created by mick on 2/26/24.
//

#include <sstream>
#include "GraphAsAdjList.h"

std::vector<int> parseWithoutWeight(const std::string &line) {
    std::vector<int> data;
    int token;
    std::istringstream token_stream(line);
    while (token_stream >> token) {
        data.push_back(token);
    }
    return data;
}

std::vector<std::pair<int, int>> parseWithWeight(const std::string &line) {
    std::vector<std::pair<int, int>> data;
    int token1;
    int token2;
    std::istringstream token_stream(line);
    while (token_stream >> token1 >> token2) {
        data.emplace_back(token1, token2);
    }
    return data;
}

void GraphAsAdjList::addEdge(int from, int to, int weight) {

}

void GraphAsAdjList::removeEdge(int from, int to) {

}

int GraphAsAdjList::changeEdge(int from, int to, int newWeight) {
    return 0;
}

void GraphAsAdjList::load(std::ifstream &input) {
    int N, D, W;
    input >> N >> D >> W;
    size = N;
    directed = D;
    weighted = W;
    for (int i = 0; i < N; i++) {
        holder.emplace_back(i);
    }
    if (weighted) {
        for (int i = 0; i < N; i++) {
            std::string line;
            getline(input, line);
            auto data = parseWithWeight(line);
            for (std::pair<int, int> vertice : data) {
                holder[i].connect(vertice.first, vertice.second);
            }
        }
    } else {
        for (int i = 0; i < N; i++) {
            std::string line;
            getline(input, line);
            auto data = parseWithoutWeight(line);
            for (int vertice : data) {
                holder[i].connect(vertice);
            }
        }
    }
}

void GraphAsAdjList::dump(std::ofstream &output) {
    output << size << '\n';
    output << directed << ' ' << weighted << '\n';
    for (const Node &node : holder) {
        for (std::pair<int, int> edge : node.children) {
            output << edge.first << ' ';
            if (weighted) {
                output << edge.second << ' ';
            }
        }
        output << '\n';
    }
}

GraphAsAdjList::~GraphAsAdjList() = default;
