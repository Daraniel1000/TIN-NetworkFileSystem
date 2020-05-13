set(TARGET "unit_tests")
project(${TARGET})
add_library(${TARGET} INTERFACE)
target_include_directories(${TARGET} INTERFACE ${PROJECT_SOURCE_DIR}/include)