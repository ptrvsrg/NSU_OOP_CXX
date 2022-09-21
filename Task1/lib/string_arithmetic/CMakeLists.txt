set(LIBRARY_NAME string_arithmetic)
set(LIBRARY_HEADERS_DIR include)
set(LIBRARY_HEADERS ${LIBRARY_HEADERS_DIR}/string_arithmetic.h)
set(LIBRARY_SOURCE_DIR src)
set(LIBRARY_SOURCE ${LIBRARY_SOURCE_DIR}/string_arithmetic.cpp)

project(${PROJECT_NAME} CXX)

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_HEADERS} ${LIBRARY_SOURCE})

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY_HEADERS_DIR})

add_subdirectory(test)