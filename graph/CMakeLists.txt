cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

set(LIBRARY_NAME graph)
set(
        SOURCE_FILES
        src/Graph.cpp
        src/Edge.cpp
        src/Node.cpp
        src/GraphAsEdgesList.cpp
        src/GraphAsAdjMatrix.cpp
        src/GraphAsAdjList.cpp
        src/DSU.cpp)

set(
        HEADER_FILES
        include/Graph.h
        include/Edge.h
        include/Node.h
        include/GraphAsEdgesList.h
        include/GraphAsAdjMatrix.h
        include/GraphAsAdjList.h
        include/InnerGraph.h
        include/DSU.h
        src/MST.cpp
        include/MST.h)

add_library(${LIBRARY_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${LIBRARY_NAME} PRIVATE include)