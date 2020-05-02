set(TARGET "server")
project(${TARGET})

# change these to proper directories where each file should be
set(SRCDIR "src")
set(BINDIR "bin")

set(SRC_FILES main.cpp) # add source files here (relative to SRCDIR)
list(TRANSFORM SRC_FILES PREPEND ${SRCDIR}/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${BINDIR})

add_executable(${TARGET} ${SRC_FILES})
target_link_libraries(${TARGET} messages socket) # add shared libraries here (relative to shared)