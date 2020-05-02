set(TARGET "socket")
project(${TARGET})

set(SRCDIR "src")
set(INCLUDEDIR "include")

set(SRC_FILES Socket.cpp) # add source files here (relative to SRCDIR)
list(TRANSFORM SRC_FILES PREPEND ${SRCDIR}/)

add_library(${TARGET} STATIC ${SRC_FILES})
target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/${INCLUDEDIR})
target_link_libraries(${TARGET} PUBLIC messages)