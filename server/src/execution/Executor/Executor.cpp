#include "Executor.h"

void Executor::run()
{
    Handler* ptr;
    while(!serverStop.try_lock())
    {
        if((ptr = messageQueue.frontSafe()) != nullptr) {
            ptr->handle();
            ptr->signalCompletion();
            messageQueue.popSafe();
        }
    }
    serverStop.unlock();
}
