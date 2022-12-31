message(STATUS "Creating library \"tournament_mode\"")

add_library(tournament_mode STATIC
        src/tournament_mode.cpp)
target_include_directories(tournament_mode PUBLIC
        include
        ../abstract_mode/include)
target_link_libraries(tournament_mode
        PUBLIC abstract_mode)