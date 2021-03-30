cmake_minimum_required(VERSION 3.5.1)

add_subdirectory(libs)

#--------------------------------------------------------------------------
#Part of simple-logger
add_executable(simple-logger main.cpp)

target_link_libraries(simple-logger logger_lib error_handle_lib -pthread)
#TODO: check macros for current project directory
target_include_directories(simple-logger PUBLIC "libs/include")
#--------------------------------------------------------------------------

#--------------------------------------------------------------------------
#Part of logger-test
add_subdirectory(tests)

add_executable(logger-test logger_test.cpp)

target_link_libraries(logger-test logger_lib error_handle_lib mock_lib -lgtest -lgtest_main -lgmock -pthread -ldl)
#TODO: check macros for current project directory
target_include_directories(logger-test PUBLIC 
                            "libs/include"                        
                            "tests/include")
#--------------------------------------------------------------------------