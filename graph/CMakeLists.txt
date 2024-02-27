set(LIBRARY_NAME graph)
set(
        SOURCE_FILES
        src/Graph.cpp
        src/Edge.cpp
        src/Node.cpp
        src/GraphAsEdgesList.cpp
)
set(
        HEADER_FILES
        include/Graph.h
        include/Edge.h
        include/Node.h
        include/GraphAsEdgesList.h src/GraphAsAdjMatrix.cpp include/GraphAsAdjMatrix.h src/GraphAsAdjList.cpp include/GraphAsAdjList.h include/InnerGraph.h)

add_library(${LIBRARY_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${LIBRARY_NAME} PRIVATE include)