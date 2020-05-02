set(TARGET "mynfs")

cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 17)
project(${TARGET})

# add shared libraries here
add_subdirectory(shared/addresses)
add_subdirectory(shared/messages)
add_subdirectory(shared/protocol)
add_subdirectory(shared/socket)
add_subdirectory(mynfslib)
add_subdirectory(server)
add_subdirectory(client)