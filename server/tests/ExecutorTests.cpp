#include <catch.hpp>
#include <thread>
#include "../src/execution/Executor/Executor.h"

SafeQueue<Handler*> queue;
class dummyHandler: public Handler
{
    DomainData data, data2;
    PlainError error;
    AccessManager manager;
public:
    bool handled = false;
    dummyHandler():manager("./testDir", "root", "hosts.txt"),
    data(),
    Handler(data,NetworkAddress(), data2, error, manager)
    {}
    void handle(){handled = true;};
};

TEST_CASE("Executor does nothing and exits when ServerStop is left unlocked", "[Executor]")
{
    Executor executor(queue);
    std::thread executorThread(&Executor::run, &executor);
    executorThread.join();
}

TEST_CASE("Executor waits on empty queue, signals completion correctly, and exits upon being notified", "[Completion]")
{
    Executor executor(queue);
    executor.serverStop.lock();
    std::thread executorThread(&Executor::run, &executor);
    dummyHandler dummy;
    queue.pushSafe(&dummy);
    dummy.waitForCompletion();
    executor.serverStop.unlock();
    queue.notify();
    executorThread.join();
    REQUIRE( dummy.handled );
}