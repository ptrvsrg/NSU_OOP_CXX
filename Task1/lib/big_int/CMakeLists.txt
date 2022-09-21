set(LIBRARY_NAME big_int)
set(LIBRARY_HEADERS_DIR include)
set(LIBRARY_HEADERS ${LIBRARY_HEADERS_DIR}/big_int.h)
set(LIBRARY_SOURCE_DIR src)
set(LIBRARY_SOURCE ${LIBRARY_SOURCE_DIR}/big_int.cpp)
set(LINK_LIBRARY string_arithmetic)

project(${PROJECT_NAME} CXX)

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_HEADERS} ${LIBRARY_SOURCE})

target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_HEADERS_DIR})

add_subdirectory(test)

target_link_libraries(${LIBRARY_NAME} PUBLIC ${LINK_LIBRARY})