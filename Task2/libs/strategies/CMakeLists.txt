cmake_minimum_required(VERSION 3.22.1)


set(LIBRARY_OUTPUT_PATH
        ${CMAKE_SOURCE_DIR}/strategy_libs)
set(TRIVIAL_STRATEGIES
        always_cooperate
        always_desert
        random)
set(NON_TRIVIAL_STRATEGIES
        tit_for_tat
        probability
        grim_trigger)


project(strategies CXX)


message(STATUS "Creating dynamic libraries of strategies ...")


foreach(TRIVIAL_STRATEGY ${TRIVIAL_STRATEGIES})
    add_subdirectory(trivial/${TRIVIAL_STRATEGY})
endforeach(TRIVIAL_STRATEGY)
foreach(NON_TRIVIAL_STRATEGY ${NON_TRIVIAL_STRATEGIES})
    add_subdirectory(non_trivial/${NON_TRIVIAL_STRATEGY})
endforeach(NON_TRIVIAL_STRATEGY)