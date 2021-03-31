cmake_minimum_required(VERSION 3.5.1)

project("Simple-logger")

add_compile_options(-fprofile-arcs -ftest-coverage)

add_library(mock_lib STATIC mock.cpp)
target_include_directories(mock_lib PUBLIC "${CMAKE_SOURCE_DIR}/tests/include")
