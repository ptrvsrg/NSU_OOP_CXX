message(STATUS "Creating library \"matrix\"")


add_library(matrix STATIC
        src/matrix.cpp)
set_target_properties(matrix PROPERTIES PREFIX "")
target_include_directories(matrix PUBLIC
        include/matrix)