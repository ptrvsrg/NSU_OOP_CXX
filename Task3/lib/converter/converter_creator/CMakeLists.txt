message(STATUS "Creating library \"converter_creator\"")

add_library(converter_creator STATIC
        src/converter_creator.cpp
        src/converter_creator_errors.cpp)

target_include_directories(converter_creator
        PUBLIC include
        PUBLIC ../converter_interface/include)
foreach(CONVERTER_SOURCE_DIR ${CONVERTER_SOURCE_DIRS})
    target_include_directories(converter_creator
            PUBLIC ${CONVERTER_SOURCE_DIR}/include)
endforeach(CONVERTER_SOURCE_DIR)

target_link_directories(converter_creator
        PUBLIC ${CMAKE_BINARY_DIR}/lib/converter/converter_interface)
foreach(CONVERTER_BINARY_DIR ${CONVERTER_BINARY_DIRS})
    target_link_directories(converter_creator
            PUBLIC ${CONVERTER_BINARY_DIR})
endforeach(CONVERTER_BINARY_DIR)

target_link_libraries(converter_creator
        PUBLIC converter_interface
        PUBLIC ${CONVERTERS})

message(STATUS "Creating tests for converter library \"converter_creator\"")

find_package(GTest)
if(NOT GTest_FOUND)
    include(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        release-1.11.0
    )
    FetchContent_MakeAvailable(googletest)
endif()
add_executable(tests_converter_creator
        test/tests_converter_creator.cpp)
target_link_libraries(tests_converter_creator
        PUBLIC converter_creator
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_converter_creator
        COMMAND tests_converter_creator
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)