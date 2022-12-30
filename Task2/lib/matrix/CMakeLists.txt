message(STATUS "Creating library \"matrix\"")

add_library(matrix STATIC
        src/matrix.cpp)
target_include_directories(matrix PUBLIC
        include/matrix
        ${CMAKE_SOURCE_DIR}/lib/strategy/strategy_interface/include)
target_link_directories(matrix
        PUBLIC ${CMAKE_BINARY_DIR}/lib/strategy/strategy_interface)
target_link_libraries(matrix
        PUBLIC strategy_interface)

message(STATUS "Creating tests for library \"matrix\"")

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
add_executable(tests_matrix
        test/tests_matrix.cpp)
target_link_libraries(tests_matrix PUBLIC
        matrix
        gtest
        gtest_main)
add_test(NAME tests_matrix
        COMMAND tests_matrix
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)