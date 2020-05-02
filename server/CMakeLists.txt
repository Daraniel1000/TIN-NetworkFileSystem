set(TARGET "server")
project(${TARGET})

set(BINDIR "bin")

set(SRC_FILES src/main.cpp) # add source files here

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${BINDIR})

add_executable(${TARGET} ${SRC_FILES})
target_link_libraries(${TARGET} messages socket) # add shared libraries here (relative to shared)