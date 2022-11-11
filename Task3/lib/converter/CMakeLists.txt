message(STATUS "Creating converter libraries")

set(SUBDIRS
        mute)

foreach(SUBDIR ${SUBDIRS})
    add_subdirectory(${SUBDIR})
endforeach(SUBDIR)