message(STATUS "Creating library \"abstract_mode\"")

add_library(abstract_mode STATIC
        src/abstract_mode.cpp)
target_include_directories(abstract_mode PUBLIC
        include/abstract_mode
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix
        ${CMAKE_SOURCE_DIR}/libs/strategies/include/strategy_creator)
target_link_directories(abstract_mode PUBLIC
        ${CMAKE_BINARY_DIR}/libs/matrix
        ${CMAKE_BINARY_DIR}/libs/strategy_creator)
target_link_libraries(abstract_mode
        PUBLIC matrix
        PUBLIC strategy_creator)

add_library(mode_creator STATIC
        src/mode_creator.cpp)
target_include_directories(mode_creator PUBLIC
        include/abstract_mode
        include/mode_creator)

set(MODES
        detailed_mode
        fast_mode
        tournament_mode)

foreach(MODE ${MODES})
    message(STATUS "Creating library \"${MODE}\"")

    add_library(${MODE} STATIC
            src/${MODE}.cpp)
    target_include_directories(${MODE} PUBLIC
            include/${MODE}
            include/abstract_mode)
    target_link_libraries(${MODE} PUBLIC
            abstract_mode)

    target_include_directories(mode_creator PUBLIC
            include/${MODE})
endforeach(MODE)

target_link_libraries(mode_creator PUBLIC
        abstract_mode
        ${MODES})