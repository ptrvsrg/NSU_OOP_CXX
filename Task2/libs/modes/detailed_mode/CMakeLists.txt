message(STATUS "Creating library \"detailed_mode\"")


add_library(detailed_mode STATIC
        src/detailed_mode.cpp)
set_target_properties(detailed_mode PROPERTIES PREFIX "")
target_include_directories(detailed_mode PUBLIC
        include/detailed_mode
        ${CMAKE_SOURCE_DIR}/libs/abstract_mode/include/abstract_mode)

link_directories(${CMAKE_BINARY_DIR}/libs/abstract_mode)
target_link_libraries(detailed_mode PUBLIC
        abstract_mode)