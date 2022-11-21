message(STATUS "Creating library \"converter_interface\"")

add_library(converter_interface INTERFACE)
target_include_directories(converter_interface
        INTERFACE include
        INTERFACE ${CMAKE_SOURCE_DIR}/lib/WAV/include)