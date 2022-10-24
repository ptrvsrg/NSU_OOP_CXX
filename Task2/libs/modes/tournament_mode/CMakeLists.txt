message(STATUS "Creating library \"tournament_mode\"")

add_library(tournament_mode STATIC
        src/tournament_mode.cpp)
target_include_directories(tournament_mode PUBLIC
        include/tournament_mode
        ${CMAKE_SOURCE_DIR}/libs/abstract_mode/include/abstract_mode)
target_link_directories(tournament_mode PUBLIC
        ${CMAKE_BINARY_DIR}/libs/abstract_mode)
target_link_libraries(tournament_mode PUBLIC
        abstract_mode)