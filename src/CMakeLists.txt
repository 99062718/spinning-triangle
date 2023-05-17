cmake_minimum_required(VERSION 3.4.1)

add_library(test_library test.cpp ${HEADER_LIST})

target_include_directories(test_library PUBLIC ../include)


source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST}
)
