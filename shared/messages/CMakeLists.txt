set(TARGET "messages")
project(${TARGET})

set(INCLUDEDIR "include")

set(SRC_FILES src/RequestMessage.cpp include/messages/RequestMessage.h src/ConfirmMessage.cpp include/messages/ConfirmMessage.h src/DataMessage.cpp include/messages/DataMessage.h src/PlainData.cpp include/messages/PlainData.h src/DomainData.cpp include/messages/DomainData.h) # add source files here

add_library(${TARGET} STATIC ${SRC_FILES})
target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/${INCLUDEDIR})