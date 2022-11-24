message(STATUS "Creating library \"iostream_errors\"")

add_library(iostream_errors STATIC
        src/iostream_errors.cpp)
target_include_directories(iostream_errors
        PUBLIC include)