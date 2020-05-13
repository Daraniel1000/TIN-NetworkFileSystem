set(TARGET "application")
project(${TARGET})

set(INCLUDEDIR "include")

set(SRC_FILES src/mynfs/requests/OpenRequest.cpp src/mynfs/replies/OpenReply.cpp) # add source files here

add_library(${TARGET} STATIC ${SRC_FILES})
target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/${INCLUDEDIR})
target_link_libraries(${TARGET} PUBLIC session transport)

add_subdirectory(tests)