set(TARGET "mynfs")

cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(${TARGET})

# add shared libraries here
add_subdirectory(test_lib)
add_subdirectory(shared/addresses)
add_subdirectory(shared/session)
add_subdirectory(shared/application)
add_subdirectory(shared/transport)
add_subdirectory(mynfslib)
add_subdirectory(server)
add_subdirectory(client)
