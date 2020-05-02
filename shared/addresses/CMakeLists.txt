set(TARGET "addresses")
project(${TARGET})

set(INCLUDEDIR "include")

set(SRC_FILES src/IpAddress.cpp src/Port.cpp include/addresses/Port.h) # add source files here

add_library(${TARGET} STATIC ${SRC_FILES})
target_include_directories(${TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/${INCLUDEDIR})