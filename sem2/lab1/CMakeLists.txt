cmake_minimum_required(VERSION 3.14)
project(lab1)

enable_testing()
add_subdirectory(googletest)
add_executable(test_app main.cpp)
target_link_libraries(test_app gtest_main gmock_main)

