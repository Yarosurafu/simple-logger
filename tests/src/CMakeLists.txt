cmake_minimum_required(VERSION 3.5.1)

add_library(mock_lib STATIC mock.cpp)
target_include_directories(mock_lib PUBLIC "../include")