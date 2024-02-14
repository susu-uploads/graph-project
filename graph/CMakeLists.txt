set(LIBRARY_NAME graph)
set(
        SOURCE_FILES
        src/Graph.cpp
        src/Edge.cpp src/Node.cpp)
set(
        HEADER_FILES
        include/Graph.h
        include/Edge.h
        include/Node.h)

add_library(${LIBRARY_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${LIBRARY_NAME} PRIVATE include)