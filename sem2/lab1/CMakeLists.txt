cmake_minimum_required(VERSION 3.26)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab1 main.cpp B-Tree.h)

add_subdirectory(Google_tests)