find_package(Threads)
add_executable(mynfslib_tests TestsMain.cpp MyNFSLibTests.cpp)
target_link_libraries(mynfslib_tests unit_tests mynfslib Threads::Threads)