cmake_minimum_required(VERSION 3.23)

set(SUBDIR
        lib/cl_parser
        lib/matrix
        lib/modes
        lib/strategy
        lib/game)
set(LIBRARY
        cl_parser
        game)
file(GLOB
        STRATEGY_SOURCE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/strategy/*")
list(REMOVE_ITEM
        STRATEGY_SOURCE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/strategy/strategy_creator
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/strategy/strategy_interface
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/strategy/CMakeLists.txt)
string(REPLACE
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/strategy/"
        ";${CMAKE_CURRENT_BINARY_DIR}/lib/strategy/"
        STRATEGY_BINARY_DIRS
        ${STRATEGY_SOURCE_DIRS})
string(REPLACE
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/strategy/"
        ";"
        STRATEGIES
        ${STRATEGY_SOURCE_DIRS})

project(Task2 CXX)

enable_testing()
foreach(SUBDIR ${SUBDIR})
    add_subdirectory(${SUBDIR})
endforeach(SUBDIR)

# Example

add_executable(Task2
        example/main.cpp)
target_link_libraries(Task2 ${LIBRARY})
add_test(NAME launch_example
        COMMAND Task2   --name
                            always_cooperate
                            always_defect
                            random
                            pavlov
                            grim_trigger
                            tit_for_tat
                            tit_for_tat_with_forgiveness
                        --mode
                            tournament
                        --steps
                            1000
                        --configs
                            config/
                        --matrix
                            matrix.txt
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/example)