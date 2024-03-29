//
// Created by mick on 29.03.24.
//


#ifndef DSU_H
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


#endif //DSU_H
