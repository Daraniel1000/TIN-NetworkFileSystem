set(TARGET "protocol")
project(${TARGET})

set(INCLUDEDIR "include")

set(SRC_FILES src/requests/OpenRequest.cpp include/protocol/requests/OpenRequest.h src/replies/OpenReply.cpp include/protocol/replies/OpenReply.h) # add source files here

add_library(${TARGET} STATIC ${SRC_FILES})
target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/${INCLUDEDIR})
target_link_libraries(${TARGET} PUBLIC messages)