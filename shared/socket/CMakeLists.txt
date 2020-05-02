set(TARGET "socket")
project(${TARGET})

set(INCLUDEDIR "include")

set(SRC_FILES src/Socket.cpp) # add source files here

add_library(${TARGET} STATIC ${SRC_FILES})
target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/${INCLUDEDIR})
target_link_libraries(${TARGET} PUBLIC addresses messages)