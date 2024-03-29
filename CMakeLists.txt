cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME graph_project)
set(
        SOURCE_FILES
        result.cpp
)

project(${PROJECT_NAME})

#add_subdirectory(graph)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#target_link_libraries(${PROJECT_NAME} PUBLIC graph)
