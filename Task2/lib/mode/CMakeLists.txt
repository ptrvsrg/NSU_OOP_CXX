file(GLOB
        MODE_SOURCE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/*")
list(REMOVE_ITEM
        MODE_SOURCE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/abstract_mode
        ${CMAKE_CURRENT_SOURCE_DIR}/mode_creator
        ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt)
string(REPLACE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        ";${CMAKE_CURRENT_BINARY_DIR}"
        MODE_BINARY_DIRS
        ${MODE_SOURCE_DIRS})
string(REPLACE
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        ";"
        MODES
        ${MODE_SOURCE_DIRS})

add_subdirectory(abstract_mode)
add_subdirectory(mode_creator)

foreach(MODE_SOURCE_DIR ${MODE_SOURCE_DIRS})
    add_subdirectory(${MODE_SOURCE_DIR})
endforeach(MODE_SOURCE_DIR)