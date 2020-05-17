set(TARGET "application")
project(${TARGET})

set(INCLUDEDIR "include")

set(SRC_FILES
        src/mynfs/requests/OpenRequest.cpp
        src/mynfs/requests/ReadRequest.cpp
        src/mynfs/replies/OpenReply.cpp
        src/mynfs/errors/OpenReplyError.cpp
        src/mynfs/requests/ReadRequest.cpp
        src/mynfs/replies/ReadReply.cpp
        src/mynfs/errors/ReadReplyError.cpp
        src/mynfs/errors/WriteReplyError.cpp
        src/mynfs/errors/LseekReplyError.cpp
        src/mynfs/errors/CloseReplyError.cpp
        src/mynfs/errors/UnlinkReplyError.cpp
        src/mynfs/replies/ReadReply.cpp
        src/mynfs/replies/WriteReply.cpp
        src/mynfs/replies/LseekReply.cpp
        src/mynfs/replies/CloseReply.cpp
        src/mynfs/replies/UnlinkReply.cpp
        src/mynfs/requests/ReadRequest.cpp
        src/mynfs/requests/WriteRequest.cpp
        src/mynfs/requests/LseekRequest.cpp
        src/mynfs/requests/CloseRequest.cpp
        src/mynfs/requests/UnlinkRequest.cpp) # add source files here

add_library(${TARGET} STATIC ${SRC_FILES})
target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/${INCLUDEDIR})
target_link_libraries(${TARGET} PUBLIC session transport)

add_subdirectory(tests)