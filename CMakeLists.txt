cmake_minimum_required(VERSION 3.4.1 FATAL_ERROR)
project(Spinning_Triangle)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

AUX_SOURCE_DIRECTORY(src SOURCES)
add_subdirectory(src)

add_executable(app ${SOURCES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lwayland-client -I${CMAKE_CURRENT_LIST_DIR}/include")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lwayland-client -I${CMAKE_CURRENT_LIST_DIR}/include")