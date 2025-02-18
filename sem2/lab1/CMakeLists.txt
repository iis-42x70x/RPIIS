cmake_minimum_required(VERSION 3.30)

project(pivo1)

set(SOURCE_EXE src/tests.cpp)

add_executable(tests ${SOURCE_EXE})

target_link_libraries(tests gtest gmock pthread)