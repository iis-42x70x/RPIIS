cmake_minimum_required(VERSION 3.27)
project(lab_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab_1
        main.cpp
        Node.hpp
        Queue.cpp
        Queue.hpp
        tests.hpp)
