cmake_minimum_required(VERSION 3.4.1 FATAL_ERROR)
project(Spinning_Triangle)

set(START main.cpp)

add_subdirectory(src)

add_executable(app ${START})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lwayland-client")