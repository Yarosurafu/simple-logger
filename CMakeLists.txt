cmake_minimum_required(VERSION 3.5.1)

add_subdirectory(libs)

add_executable(simple-logger main.cpp)

target_link_libraries(simple-logger logger_lib error_handle_lib -pthread)

target_include_directories(simple-logger PUBLIC "libs/include")