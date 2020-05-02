set(TARGET "mynfslib")
project(${TARGET})

set(SRCDIR "src")
set(INCLUDEDIR "include")
set(LIBDIR "lib")

set(SRC_FILES mynfslib.cpp) # add source files here (relative to SRCDIR)
list(TRANSFORM SRC_FILES PREPEND ${SRCDIR}/)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${LIBDIR})

add_library(${TARGET} STATIC ${SRC_FILES})
target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/${INCLUDEDIR})
target_link_libraries(${TARGET} PUBLIC messages socket)