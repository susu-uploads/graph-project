//
// Created by mick on 29.03.24.
//

#include "DSU.h"

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
