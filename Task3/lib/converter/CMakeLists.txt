add_subdirectory(converter_creator)
add_subdirectory(converter_errors)
add_subdirectory(converter_interface)

foreach(CONVERTER_SOURCE_DIR ${CONVERTER_SOURCE_DIRS})
    add_subdirectory(${CONVERTER_SOURCE_DIR})    
endforeach(CONVERTER_SOURCE_DIR)