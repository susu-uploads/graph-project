cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

set(LIBRARY_NAME util)
set(
        SOURCE_FILES
        src/DSU.cpp)
set(
        HEADER_FILES
        include/DSU.h)

add_library(${LIBRARY_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${LIBRARY_NAME} PRIVATE include)