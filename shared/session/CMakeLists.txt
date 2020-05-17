set(TARGET "session")
project(${TARGET})

set(INCLUDEDIR "include")

set(SRC_FILES
        src/messages/RequestMessage.cpp
        src/messages/ConfirmMessage.cpp
        src/messages/DataMessage.cpp
        src/DomainData.cpp
        src/messages/Message.cpp
        src/Converter.cpp) # add source files here

add_library(${TARGET} STATIC ${SRC_FILES})
target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/${INCLUDEDIR})
target_link_libraries(${TARGET} PUBLIC transport)

add_subdirectory(tests)