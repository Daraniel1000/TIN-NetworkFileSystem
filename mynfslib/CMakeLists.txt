set(TARGET "mynfslib")
project(${TARGET})

set(INCLUDEDIR "include")
set(LIBDIR "lib")

set(SRC_FILES src/mynfslib.cpp src/endpoint/ClientEndpoint.cpp) # add source files here

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${LIBDIR})

add_library(${TARGET} STATIC ${SRC_FILES})
target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/${INCLUDEDIR})
target_link_libraries(${TARGET} PUBLIC application session transport addresses)