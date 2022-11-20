message(STATUS "Creating library \"sound_processor\"")

add_library(sound_processor STATIC
        src/sound_processor.cpp)
target_include_directories(sound_processor
        PUBLIC include/sound_processor)
target_link_directories(sound_processor
        PUBLIC ${CMAKE_BINARY_DIR}/lib/config_parser
        PUBLIC ${CMAKE_BINARY_DIR}/lib/converters
        PUBLIC ${CMAKE_BINARY_DIR}/lib/WAV)
target_link_libraries(sound_processor
        PUBLIC config_parser
        PUBLIC converter_creator
        PUBLIC WAV)