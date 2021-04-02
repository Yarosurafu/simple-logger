cmake_minimum_required(VERSION 3.5.1)

project("Simple-logger")

add_compile_options(-fprofile-arcs -ftest-coverage)

add_subdirectory(libs)

#--------------------------------------------------------------------------
#Part of simple-logger
add_executable(simple-logger main.cpp)

target_link_libraries(simple-logger logger_lib error_handle_lib -pthread -lgcov --coverage)
target_include_directories(simple-logger PUBLIC "${CMAKE_SOURCE_DIR}/libs/include")
#--------------------------------------------------------------------------

#--------------------------------------------------------------------------
#Part of logger-test
add_subdirectory(tests)

add_executable(logger-test logger_test.cpp)
target_link_libraries(logger-test logger_lib error_handle_lib mock_lib -lgtest -lgtest_main -lgmock -pthread -ldl -lgcov --coverage)
target_include_directories(logger-test PUBLIC 
                            "${CMAKE_SOURCE_DIR}/libs/include"                        
                            "${CMAKE_SOURCE_DIR}/tests/include")
#--------------------------------------------------------------------------

add_executable(robot-test robot_test.cpp)
target_link_libraries(robot-test logger_lib error_handle_lib -lgtest -lgtest_main -lgmock -pthread -ldl -lgcov --coverage)
target_include_directories(robot-test PUBLIC 
                            "${CMAKE_SOURCE_DIR}/libs/include")