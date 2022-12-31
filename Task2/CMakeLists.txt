cmake_minimum_required(VERSION 3.23)

set(SUBDIR
        lib/cl_parser
        lib/matrix
        lib/mode
        lib/strategy
        lib/game)
set(LIBRARY
        cl_parser
        game)

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