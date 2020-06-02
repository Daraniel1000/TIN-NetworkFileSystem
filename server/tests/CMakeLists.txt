add_executable(server_tests TestsMain.cpp
                            HandlersTests.cpp
                            ../src/execution/handlers/OpenHandler.cpp
                            ../src/execution/handlers/ReadHandler.cpp
                            ../src/execution/handlers/CloseHandler.cpp
                            ../src/execution/handlers/UnlinkHandler.cpp
                            ../src/execution/handlers/LseekHandler.cpp
                            ../src/execution/handlers/WriteHandler.cpp
                            AccessManagerTests.cpp
                            ../src/AccessManager.cpp
                            ../src/execution/Executor/Executor.cpp
                            SafeQueueTests.cpp
                            ExecutorTests.cpp)
find_package(Threads)
target_link_libraries(server_tests unit_tests application addresses session transport Threads::Threads)