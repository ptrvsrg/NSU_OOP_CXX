cmake_minimum_required(VERSION 3.5.1)
project(task0 CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE module1 module2 module3)

add_subdirectory(module1)
add_subdirectory(module2)
add_subdirectory(module3)

target_link_libraries(${PROJECT_NAME} PRIVATE module1_lib module2_lib module3_lib)