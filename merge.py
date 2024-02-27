from typing import Tuple, TextIO

EDGE_H: str = "graph/include/Edge.h"
EDGE_S: str = "graph/src/Edge.cpp"

NODE_H: str = "graph/include/Node.h"
NODE_S: str = "graph/src/Node.cpp"

INNER_GRAPH_H: str = "graph/include/InnerGraph.h"

ADJ_LIST_GRAPH_H: str = "graph/include/GraphAsAdjList.h"
ADJ_LIST_GRAPH_S: str = "graph/src/GraphAsAdjList.cpp"

ADJ_MATRIX_H: str = "graph/include/GraphAsAdjMatrix.h"
ADJ_MATRIX_S: str = "graph/src/GraphAsAdjMatrix.cpp"

EDJ_LIST_H: str = "graph/include/GraphAsEdgesList.h"
EDJ_LIST_S: str = "graph/src/GraphAsEdgesList.cpp"

GRAPH_H: str = "graph/include/Graph.h"
GRAPH_S: str = "graph/src/Graph.cpp"


def write_default(file: TextIO, source_name: str):
    source: TextIO = open(source_name, "r")
    lines = list(filter(lambda x: not x.startswith("//"), source.readlines()))
    lines = list(filter(lambda x: not x.endswith(".h\"\n"), lines))
    lines = list(filter(lambda x: not x.endswith(".h>\n"), lines))
    file.writelines(lines)
    source.close()


def write_edge(file: TextIO):
    write_default(file, EDGE_H)
    write_default(file, EDGE_S)


def write_node(file: TextIO):
    write_default(file, NODE_H)
    write_default(file, NODE_S)


def write_util_graph(file: TextIO):
    write_default(file, INNER_GRAPH_H)
    write_default(file, ADJ_LIST_GRAPH_H)
    write_default(file, ADJ_LIST_GRAPH_S)
    write_default(file, ADJ_MATRIX_H)
    write_default(file, ADJ_MATRIX_S)
    write_default(file, EDJ_LIST_H)
    write_default(file, EDJ_LIST_S)


def write_graph(file: TextIO):
    write_default(file, GRAPH_H)
    write_default(file, GRAPH_S)


if __name__ == "__main__":
    file: TextIO = open("result.cpp", "w")
    write_edge(file)
    write_node(file)
    write_util_graph(file)
    write_graph(file)
    file.close()
