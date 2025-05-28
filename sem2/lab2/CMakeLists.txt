cmake_minimum_required(VERSION 3.27)
project(2lab)


set(CMAKE_CXX_STANDARD 14)

include_directories(.)
add_subdirectory(Set_lib)
add_executable(2lab
         main.cpp
         Set_lib/Set.cpp
         Set_lib/Set.hpp
)

add_subdirectory(Google_tests)

