message(STATUS "Creating library of strategy \"pavlov\" ")
add_library(pavlov STATIC
        src/pavlov.cpp)
target_include_directories(pavlov PUBLIC
        include
        ../strategy_interface/include)
target_link_directories(pavlov
        PUBLIC ${CMAKE_BINARY_DIR}lib/strategy/strategy_interface
        PUBLIC ${CMAKE_BINARY_DIR}lib/strategy/strategy_creator)
target_link_libraries(pavlov
        PUBLIC strategy_interface
        PUBLIC strategy_creator)

find_package(Boost)
if (NOT Boost_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            Boost
            GIT_REPOSITORY https://github.com/boostorg/boost.git
            GIT_TAG boost-1.80.0
    )
    FetchContent_MakeAvailable(Boost)
endif()

target_compile_definitions(pavlov PUBLIC
        -DBOOST_BIND_GLOBAL_PLACEHOLDERS)
target_link_directories(pavlov
        PUBLIC Boost::property_tree)

message(STATUS "Creating tests for library of strategy \"pavlov\"")

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

add_executable(tests_pavlov
        test/tests_pavlov.cpp)
target_link_libraries(tests_pavlov PUBLIC
        pavlov
        gtest
        gtest_main)
add_test(NAME tests_pavlov
        COMMAND tests_pavlov
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)