set(LIBRARY_NAME big_int)
set(LIBRARY_HEADERS_DIR include)
set(LIBRARY_HEADERS include/big_int.h)
set(LIBRARY_SOURCE src/big_int.cpp)
set(LINK_LIBRARY string_arithmetic)
set(TEST_LIBRARY_NAME tests_big_int)
set(TEST_SOURCE test/tests_big_int.cpp)

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_HEADERS} ${LIBRARY_SOURCE})
target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_HEADERS_DIR})
target_link_libraries(${LIBRARY_NAME} PUBLIC ${LINK_LIBRARY})

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(${TEST_LIBRARY_NAME} ${TEST_SOURCE})
target_link_libraries(${TEST_LIBRARY_NAME} gtest_main ${LIBRARY_NAME})