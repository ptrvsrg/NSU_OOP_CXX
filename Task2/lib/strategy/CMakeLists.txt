add_subdirectory(strategy_creator)
add_subdirectory(strategy_interface)

foreach(STRATEGY_SOURCE_DIR ${STRATEGY_SOURCE_DIRS})
    add_subdirectory(${STRATEGY_SOURCE_DIR})
endforeach(STRATEGY_SOURCE_DIR)