message(STATUS "Creating library of strategy \"tit_for_tat_with_forgiveness\" ")
add_library(tit_for_tat_with_forgiveness STATIC
        src/tit_for_tat_with_forgiveness.cpp)
target_include_directories(tit_for_tat_with_forgiveness PUBLIC
        include
        ../strategy_interface/include)
target_link_directories(tit_for_tat_with_forgiveness
        PUBLIC ${CMAKE_BINARY_DIR}lib/strategy/strategy_interface)
target_link_libraries(tit_for_tat_with_forgiveness
        PUBLIC strategy_interface)

find_package(Boost)
if (NOT Boost_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            Boost
            GIT_REPOSITORY https://github.com/boostorg/boost.git
            GIT_TAG boost-1.80.0
    )
    FetchContent_MakeAvailable(Boost)

    target_link_libraries(tit_for_tat_with_forgiveness
            PUBLIC Boost::property_tree)
else()
    target_include_directories(tit_for_tat_with_forgiveness
            PUBLIC ${Boost_INCLUDE_DIRS})
endif()

target_compile_definitions(tit_for_tat_with_forgiveness
        PUBLIC -DBOOST_BIND_GLOBAL_PLACEHOLDERS)

message(STATUS "Creating tests for library of strategy \"tit_for_tat_with_forgiveness\"")

find_package(GTest)
if (NOT GTest_FOUND)
    include(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        release-1.11.0
    )
    FetchContent_MakeAvailable(googletest)
endif ()

add_executable(tests_tit_for_tat_with_forgiveness
        test/tests_tit_for_tat_with_forgiveness.cpp)
target_link_libraries(tests_tit_for_tat_with_forgiveness PUBLIC
        tit_for_tat_with_forgiveness
        gtest
        gtest_main)
add_test(NAME tests_tit_for_tat_with_forgiveness
        COMMAND tests_tit_for_tat_with_forgiveness
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)