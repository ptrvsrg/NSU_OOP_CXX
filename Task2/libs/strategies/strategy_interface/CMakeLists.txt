message(STATUS "Creating strategy interface")

add_library(strategy_interface INTERFACE)
target_include_directories(strategy_interface INTERFACE
        include/strategy_interface)