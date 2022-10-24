set(SUBDIRS
        abstract_mode
        detailed_mode
        fast_mode
        tournament_mode
        mode_creator)

foreach(SUBDIR ${SUBDIRS})
    add_subdirectory(${SUBDIR})
endforeach(SUBDIR)