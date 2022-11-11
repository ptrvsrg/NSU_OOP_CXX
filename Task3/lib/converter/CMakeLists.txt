message(STATUS "Creating converter libraries")

set(SUBDIRS
        mute
        mix)

foreach(SUBDIR ${SUBDIRS})
    add_subdirectory(${SUBDIR})
endforeach(SUBDIR)