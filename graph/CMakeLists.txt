set(LIBRARY_NAME graph)
set(
        SOURCE_FILES
        src/Graph.cpp
        src/GraphIoHelper.cpp)
set(
        HEADER_FILES
        include/Graph.h
        include/GraphIoHelper.h)

add_library(${LIBRARY_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${LIBRARY_NAME} PRIVATE include)