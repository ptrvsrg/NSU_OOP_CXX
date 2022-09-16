cmake_minimum_required(VERSION 3.5.1)
project(task1 CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(task2 main.cpp)
add_subdirectory(big_int)
target_link_libraries(task2 PUBLIC big_int)
target_include_directories(task2 PUBLIC big_int)