#ifndef MYNFS_EXECUTOR_H
#define MYNFS_EXECUTOR_H

#include <queue>
#include "../handlers/Handler.h"
#include "../../SafeQueue.h"

class Executor {
    SafeQueue<Handler*>& messageQueue;
public:
    std::mutex serverStop;

    Executor(SafeQueue<Handler*>& q): messageQueue(q) {}

    void run();

};


#endif //MYNFS_EXECUTOR_H
