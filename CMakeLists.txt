cmake_minimum_required(VERSION 3.5.1)

add_subdirectory(libs)

add_executable(logger-test main.cpp)

target_link_libraries(logger-test logger_lib error_handle_lib -pthread)

target_include_directories(logger-test PUBLIC "libs/include")