cmake_minimum_required(VERSION 3.5.1)
project(task0 CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(task0 main.cpp)

target_include_directories(task0 PRIVATE module1 module2)

add_subdirectory(module1)
add_subdirectory(module2)

target_link_libraries(task0 PRIVATE module1_lib module2_lib)