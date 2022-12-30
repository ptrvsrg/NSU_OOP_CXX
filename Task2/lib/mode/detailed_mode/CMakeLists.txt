message(STATUS "Creating library \"detailed_mode\"")

add_library(detailed_mode STATIC
        src/detailed_mode.cpp)
target_include_directories(detailed_mode PUBLIC
        include
        ../abstract_mode/include)
target_link_libraries(detailed_mode
        PUBLIC abstract_mode)