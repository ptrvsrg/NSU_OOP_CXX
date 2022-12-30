file(GLOB
        STRATEGY_SOURCE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/*")
list(REMOVE_ITEM
        STRATEGY_SOURCE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/strategy_creator
        ${CMAKE_CURRENT_SOURCE_DIR}/strategy_interface
        ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt)
string(REPLACE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        ";${CMAKE_CURRENT_BINARY_DIR}"
        STRATEGY_BINARY_DIRS
        ${STRATEGY_SOURCE_DIRS})
string(REPLACE
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        ";"
        STRATEGIES
        ${STRATEGY_SOURCE_DIRS})

add_subdirectory(strategy_creator)
add_subdirectory(strategy_interface)

foreach(STRATEGY_SOURCE_DIR ${STRATEGY_SOURCE_DIRS})
    add_subdirectory(${STRATEGY_SOURCE_DIR})
endforeach(STRATEGY_SOURCE_DIR)