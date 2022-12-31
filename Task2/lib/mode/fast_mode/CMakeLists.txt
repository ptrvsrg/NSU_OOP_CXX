message(STATUS "Creating library \"fast_mode\"")

add_library(fast_mode STATIC
        src/fast_mode.cpp)
target_include_directories(fast_mode PUBLIC
        include
        ../abstract_mode/include)
target_link_libraries(fast_mode
        PUBLIC abstract_mode)