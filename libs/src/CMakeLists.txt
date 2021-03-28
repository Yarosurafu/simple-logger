cmake_minimum_required(VERSION 3.5.1)

add_library(error_handle_lib STATIC error_handle.cpp)
add_library(logger_lib STATIC logger.cpp)

target_include_directories(error_handle_lib PUBLIC "../include")
target_include_directories(logger_lib PUBLIC "../include")