cmake_minimum_required(VERSION 3.5.1)

add_subdirectory(logger)

add_executable(logger-test main.cpp)

target_link_libraries(logger-test logger_lib -pthread)

target_include_directories(logger-test PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/logger")