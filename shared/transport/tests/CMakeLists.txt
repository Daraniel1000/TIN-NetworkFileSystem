find_package(Threads)
add_executable(transport_tests TestsMain.cpp SocketTests.cpp PlainDataTests.cpp)
target_link_libraries(transport_tests unit_tests transport Threads::Threads)