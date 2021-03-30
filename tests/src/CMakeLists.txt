cmake_minimum_required(VERSION 3.5.1)

add_library(mock_lib STATIC mock.cpp)
#TODO: check macros for current project directory
target_include_directories(mock_lib PUBLIC "../include")
