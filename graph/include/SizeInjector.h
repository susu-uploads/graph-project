//
// Created by mick on 2/14/24.
//

#ifndef GRAPH_PROJECT_SIZEINJECTOR_H
#define GRAPH_PROJECT_SIZEINJECTOR_H

struct SizeInjector {
    void operator () (const Graph &graph);
};

void SizeInjector::operator()(const Graph &graph) {

}

#endif //GRAPH_PROJECT_SIZEINJECTOR_H
