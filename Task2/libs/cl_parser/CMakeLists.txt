message(STATUS "Creating library \"cl_parser\"")

find_package(Boost COMPONENTS program_options REQUIRED)
if(NOT Boost_FOUND)
    message("Boost not found")
    message("Installing Boost")
    include(FetchContent)
    FetchContent_Declare(
            Boost
            GIT_REPOSITORY https://github.com/boostorg/boost.git
            GIT_TAG boost-1.74.0
    )
    FetchContent_MakeAvailable(Boost)
endif()

add_library(cl_parser STATIC
        src/cl_parser.cpp)
set_target_properties(cl_parser PROPERTIES PREFIX "")
target_include_directories(cl_parser PUBLIC
        include/cl_parser
        ${Boost_INCLUDE_DIR})
target_link_libraries(cl_parser PUBLIC ${Boost_LIBRARIES})

enable_testing()
find_package(GTest REQUIRED)
if(NOT GTest_FOUND)
    message("GTest not found")
    message("Installing GTest")
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
    )
    FetchContent_MakeAvailable(googletest)
endif()

add_executable(tests_cl_parser
        test/tests_cl_parser.cpp)
target_link_libraries(tests_cl_parser PUBLIC
        cl_parser
        gtest
        gtest_main)