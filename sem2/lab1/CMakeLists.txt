cmake_minimum_required(VERSION 3.26)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab1 main.cpp B-Tree.h)

include(GoogleTest)
find_package(GTest REQUIRED)

add_executable(lab1-tests test1.cpp test2.cpp test3.cpp library.h b-tree_tree.cpp)
target_link_libraries(lab1-tests LINK_PUBLIC GTest::gtest_main)
