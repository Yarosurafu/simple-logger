cmake_minimum_required(VERSION 3.5)

add_library(logger STATIC logger.cpp)

add_executable(main main.cpp)
target_link_libraries(main logger -pthread)