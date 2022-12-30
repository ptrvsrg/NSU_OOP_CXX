message(STATUS "Creating library \"cl_parser\"")

add_library(cl_parser STATIC
        src/cl_parser.cpp)
find_package(Boost
        COMPONENTS program_options)
if (NOT Boost_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            Boost
            GIT_REPOSITORY https://github.com/boostorg/boost.git
            GIT_TAG boost-1.80.0
    )
    FetchContent_MakeAvailable(Boost)
endif()
target_include_directories(cl_parser PUBLIC
        include
        ${Boost_INCLUDE_DIRS})
target_link_libraries(cl_parser PUBLIC
        Boost::program_options)

message(STATUS "Creating tests for library \"cl_parser\"")

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
add_executable(tests_cl_parser
        test/tests_cl_parser.cpp)
target_link_libraries(tests_cl_parser PUBLIC
        cl_parser
        gtest
        gtest_main)
add_test(NAME tests_cl_parser
        COMMAND tests_cl_parser)