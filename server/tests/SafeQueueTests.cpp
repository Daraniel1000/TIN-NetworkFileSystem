#include <catch.hpp>
#include <thread>
#include <memory>
#include "../src/SafeQueue.h"

SafeQueue<int*> testQueue;
int* ret;
std::mutex m;
void frontFun()
{
    m.unlock();
    ret = testQueue.frontSafe();
}

TEST_CASE("Pop waits on an empty queue, and executes when no longer empty", "[Pop]")
{
    std::thread popThread(&SafeQueue<int*>::popSafe, &testQueue);
    std::unique_ptr<int> uniquePtr = std::make_unique<int>();
    *uniquePtr = 5;
    testQueue.pushSafe(uniquePtr.get());
    popThread.join();
    REQUIRE( testQueue.emptySafe() );
    ret = nullptr;
    std::thread frontThread(&frontFun);
    testQueue.pushSafe(uniquePtr.get());
    frontThread.join();
    REQUIRE( ret == uniquePtr.get() );
    testQueue.popSafe();
}

TEST_CASE("Front exits on notify from another thread", "[notify]")
{
    m.lock();
    std::thread frontThread(&frontFun);
    m.lock();
    testQueue.notify();
    m.unlock();
    frontThread.join();
    REQUIRE( ret== nullptr );
}