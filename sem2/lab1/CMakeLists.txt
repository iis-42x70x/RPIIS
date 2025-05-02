cmake_minimum_required(VERSION 3.27)
project(rbtree)

set(CMAKE_CXX_STANDARD 17)

add_executable(rbtree main.cpp
        Header.h
        function.cpp)
