cmake_minimum_required(VERSION 3.14)
project(MyProject VERSION 1.0)

# Указываем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем путь к Google Test
set(GTEST_DIR "D:/2sem/пиоивис/googletest/googletest-main/build")

# Подключаем include-папку Google Test
include_directories(${GTEST_DIR}/../googletest/include)

# Добавляем папку с библиотеками
link_directories(${GTEST_DIR}/lib/Debug)

# Добавляем основной проект
add_executable(my_program main.cpp set_operations.cpp)

# Добавляем тесты
add_executable(run_tests tests/test_set_operations.cpp set_operations.cpp)

# Линкуем Google Test для тестов
target_link_libraries(run_tests gtest gtest_main)

# Указываем стандарт C++ для целей
set_target_properties(my_program PROPERTIES CXX_STANDARD 17)
set_target_properties(run_tests PROPERTIES CXX_STANDARD 17)


