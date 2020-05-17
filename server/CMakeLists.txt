set(TARGET "server")
project(${TARGET})

set(BINDIR "bin")

set(SRC_FILES
        src/main.cpp
        src/endpoint/ServerEndpoint.cpp
        src/execution/HandlerFactoryPool.cpp
        src/execution/handlers/OpenHandler.cpp
        src/endpoint/ServerSubEndpoint.cpp
        src/execution/handlers/Handler.cpp
        src/execution/Executor/Executor.cpp
        src/execution/handlers/ReadHandler.cpp
        src/execution/handlers/WriteHandler.cpp
        src/execution/handlers/LseekHandler.cpp
        src/execution/handlers/CloseHandler.cpp
        src/execution/handlers/UnlinkHandler.cpp) # add source files here

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${BINDIR})
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)

add_executable(${TARGET} ${SRC_FILES})
target_link_libraries(${TARGET} PUBLIC application session transport addresses Threads::Threads) # add shared libraries here (relative to shared)

add_subdirectory(tests)