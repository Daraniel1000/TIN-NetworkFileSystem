#include "Executor.h"

void Executor::run()
{
    while(!this->serverStop.try_lock())
    {
        messageQueue.front()->handle();
        messageQueue.pop();
    }
    while(!messageQueue.empty())
    {
        messageQueue.front()->fail();
        messageQueue.pop();
    }
}
