message(STATUS "Creating library \"cl_parser\"")

set(CONVERTERS_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/config/converters_desc.json")
configure_file(include/cl_parser.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/include/cl_parser.h)

add_library(cl_parser STATIC
        src/cl_parser.cpp)
target_include_directories(cl_parser
        PUBLIC include
        PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include)
find_package(Boost
        COMPONENTS container program_options)
if (NOT Boost_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            Boost
            GIT_REPOSITORY https://github.com/boostorg/boost.git
            GIT_TAG boost-1.80.0
    )
    FetchContent_MakeAvailable(Boost)
endif()
target_link_libraries(cl_parser
        INTERFACE Boost::headers
        PUBLIC Boost::container
        PUBLIC Boost::program_options)
target_compile_definitions(cl_parser
        PUBLIC -DBOOST_BIND_GLOBAL_PLACEHOLDERS)

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
target_link_libraries(tests_cl_parser
        PUBLIC cl_parser
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_cl_parser
        COMMAND tests_cl_parser
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)