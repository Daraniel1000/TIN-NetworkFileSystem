set(TARGET "application")
project(${TARGET})

set(INCLUDEDIR "include")

set(SRC_FILES src/mynfs/requests/OpenRequest.cpp src/mynfs/requests/ReadRequest.cpp src/mynfs/replies/OpenReply.cpp src/mynfs/errors/OpenReplyError.cpp include/application/mynfs/replies/ReadReply.h include/application/mynfs/errors/ReadReplyError.h include/application/mynfs/requests/ReadRequest.h src/mynfs/requests/ReadRequest.cpp src/mynfs/replies/ReadReply.cpp) # add source files here

add_library(${TARGET} STATIC ${SRC_FILES})
target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/${INCLUDEDIR})
target_link_libraries(${TARGET} PUBLIC session transport)

add_subdirectory(tests)