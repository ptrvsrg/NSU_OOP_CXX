message(STATUS "Creating library \"mode_creator\"")

add_library(mode_creator STATIC
        src/mode_creator.cpp)
target_include_directories(mode_creator PUBLIC
        include
        ../abstract_mode/include)

foreach(MODE_SOURCE_DIR ${MODE_SOURCE_DIRS})
    target_include_directories(mode_creator
            PUBLIC ${MODE_SOURCE_DIR}/include)
endforeach(MODE_SOURCE_DIR)

target_link_libraries(mode_creator PUBLIC
        abstract_mode
        ${MODES})

message(STATUS "Creating tests for library of strategy \"mode_creator\"")
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

add_executable(tests_mode_creator
        test/tests_mode_creator.cpp)
target_link_libraries(tests_mode_creator PUBLIC
        mode_creator
        gtest
        gtest_main)
add_test(NAME tests_mode_creator
        COMMAND tests_mode_creator
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)