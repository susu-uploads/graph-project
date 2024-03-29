import os
import re
from functools import reduce
from typing import Tuple, TextIO, List, Pattern

FORBIDDEN_LINES: List[str] = [
    r"#include [\" | \<].*.h[\" | \>]",
    r"\/\/.*",
    r"#ifndef.*",
    r"#endif.*"
]

NAMESPACES_ORDER: List[str] = [
    "Edge.h",
    "Edge.cpp",
    "Node.h",
    "Node.cpp",
    "DSU.h",
    "DSU.cpp",
    "InnerGraph.h",
    "GraphAsAdjList.h",
    "GraphAsAdjList.cpp",
    "GraphAsAdjMatrix.h",
    "GraphAsAdjMatrix.cpp",
    "GraphAsEdgesList.h",
    "GraphAsEdgesList.cpp",
    "Graph.h",
    "MST.h",
    "MST.cpp",
    "Graph.cpp"
]

MAIN_TEMPLATE: str = """
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
"""

flat_map = lambda f, xs: reduce(lambda a, b: a + b, map(f, xs))


def as_source(path: str, patterns: List[Pattern[str]]) -> Tuple[int, List[str]]:
    src_file: TextIO = open(path, "r")
    src_lines: List[str] = list()
    for line in src_file.readlines():
        is_ok: bool = True
        for pattern in patterns:
            if pattern.match(line):
                is_ok = False
                break
        if is_ok:
            src_lines.append(line)

    order: int = -1
    name: str = path.split("/")[-1]  # TODO
    for index, namespace in enumerate(NAMESPACES_ORDER):
        if name == namespace:
            order = index
    return order, src_lines


if __name__ == "__main__":
    cwd: str = os.getcwd()
    sources: List[Tuple[int, List[str]]] = list()
    regexes = list(map(lambda x: re.compile(x), FORBIDDEN_LINES))

    file: TextIO = open("result.cpp", "w")
    for path, subdirs, files in os.walk(os.path.join(cwd, "graph")):
        for name in files:
            if name in NAMESPACES_ORDER:
                sources.append(as_source(os.path.join(path, name), regexes))
    sources.sort(key=lambda x: x[0])
    for lines in map(lambda x: x[1], sources):
        file.writelines(lines)
    file.write(MAIN_TEMPLATE)
    file.close()
