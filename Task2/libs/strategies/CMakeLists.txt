message(STATUS "Creating strategy interface")

add_library(strategy_interface INTERFACE)
target_include_directories(strategy_interface INTERFACE
        include/strategy_interface)

add_library(strategy_creator STATIC
        src/strategy_creator.cpp)
target_include_directories(strategy_creator PUBLIC
        include/strategy_creator
        include/strategy_interface
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix)

set(STRATEGIES
        always_cooperate
        always_defect
        grim_trigger
        pavlov
        random
        tit_for_tat
        tit_for_tat_with_forgiveness)

foreach(STRATEGY ${STRATEGIES})
    message(STATUS "Creating library of strategy \"${STRATEGY}\" ")
    add_library(${STRATEGY} STATIC
            src/${STRATEGY}.cpp)
    target_include_directories(${STRATEGY} PUBLIC
            include/${STRATEGY}
            include/strategy_interface)
    target_link_libraries(${STRATEGY}
            INTERFACE strategy_interface)
    target_include_directories(strategy_creator PUBLIC
            include/${STRATEGY})
endforeach(STRATEGY)

target_link_libraries(strategy_creator
        PUBLIC matrix
        PUBLIC ${STRATEGIES}
        INTERFACE strategy_interface)

find_package(Boost COMPONENTS container REQUIRED)
target_compile_definitions(pavlov PUBLIC
        -DBOOST_BIND_GLOBAL_PLACEHOLDERS)
target_compile_definitions(tit_for_tat_with_forgiveness PUBLIC
        -DBOOST_BIND_GLOBAL_PLACEHOLDERS)

target_link_libraries(pavlov PUBLIC
        ${Boost_LIBRARIES})
target_link_libraries(pavlov PUBLIC
        strategy_creator)
target_link_libraries(tit_for_tat_with_forgiveness PUBLIC
        ${Boost_LIBRARIES})

enable_testing()
find_package(GTest REQUIRED)
set(TESTS
        grim_trigger
        pavlov
        strategy_creator
        tit_for_tat
        tit_for_tat_with_forgiveness)

foreach(TEST ${TESTS})
    message(STATUS "Creating tests for library of strategy \"${TEST}\"")
    add_executable(tests_${TEST}
            test/tests_${TEST}.cpp)
    target_link_libraries(tests_${TEST} PUBLIC
            ${TEST}
            gtest
            gtest_main)
endforeach(TEST)