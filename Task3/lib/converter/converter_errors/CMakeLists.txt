message(STATUS "Creating library \"converter_errors\"")

add_library(converter_errors STATIC
        src/converter_errors.cpp)
target_include_directories(converter_errors
        PUBLIC include)