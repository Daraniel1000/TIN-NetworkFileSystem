set(TARGET "mynfs")

cmake_minimum_required(VERSION 3.0.2)
project(${TARGET})

# add shared libraries here
add_subdirectory(shared/messages)
add_subdirectory(shared/socket)
add_subdirectory(mynfslib)
add_subdirectory(server)
add_subdirectory(client)