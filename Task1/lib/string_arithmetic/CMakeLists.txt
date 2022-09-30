set(LIBRARY_NAME string_arithmetic)
set(LIBRARY_HEADERS_DIR include)
set(LIBRARY_HEADERS include/string_arithmetic.h)
set(LIBRARY_SOURCE src/string_arithmetic.cpp)
set(TEST_LIBRARY_NAME tests_string_arithmetic)
set(TEST_SOURCE test/tests_string_arithmetic.cpp)

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_HEADERS} ${LIBRARY_SOURCE})
target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_HEADERS_DIR})

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(${TEST_LIBRARY_NAME} ${TEST_SOURCE})
target_link_libraries(${TEST_LIBRARY_NAME} gtest_main ${LIBRARY_NAME})