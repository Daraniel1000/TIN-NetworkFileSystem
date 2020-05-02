set(TARGET "messages")
project(${TARGET})

set(INCLUDEDIR "include")

set(SRC_FILES src/Message.cpp) # add source files here

add_library(${TARGET} STATIC ${SRC_FILES})
target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/${INCLUDEDIR})