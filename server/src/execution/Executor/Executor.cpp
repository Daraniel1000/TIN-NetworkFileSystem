#include "Executor.h"

void Executor::run()
{
    while(!serverStop.try_lock())
    {
        messageQueue.frontSafe()->handle();
        messageQueue.popSafe();
    }
    while(!messageQueue.emptySafe())
    {
        messageQueue.frontSafe()->fail();
        messageQueue.popSafe();
    }
    serverStop.unlock();
}
