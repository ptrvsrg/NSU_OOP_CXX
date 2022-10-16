set(MODES
        detailed_mode
        fast_mode
        tournament_mode)

message(STATUS "Creating libraries of modes ...")

foreach(MODE ${MODES})
    add_subdirectory(${MODE})
endforeach(MODE)