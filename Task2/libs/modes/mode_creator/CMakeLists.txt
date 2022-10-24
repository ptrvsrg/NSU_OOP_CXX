message(STATUS "Creating library \"mode_creator\"")

add_library(mode_creator STATIC
        src/mode_creator.cpp)
target_include_directories(mode_creator PUBLIC
        include/mode_creator
        ${CMAKE_SOURCE_DIR}/libs/modes/abstract_mode/include/abstract_mode
        ${CMAKE_SOURCE_DIR}/libs/modes/detailed_mode/include/detailed_mode
        ${CMAKE_SOURCE_DIR}/libs/modes/fast_mode/include/fast_mode
        ${CMAKE_SOURCE_DIR}/libs/modes/tournament_mode/include/tournament_mode)
target_link_directories(mode_creator PUBLIC
        ${CMAKE_BINARY_DIR}/libs/modes/abstract_mode
        ${CMAKE_BINARY_DIR}/libs/modes/detailed_mode
        ${CMAKE_BINARY_DIR}/libs/modes/fast_mode
        ${CMAKE_BINARY_DIR}/libs/modes/tournament_mode)
target_link_libraries(mode_creator PUBLIC
        abstract_mode
        detailed_mode
        fast_mode
        tournament_mode)