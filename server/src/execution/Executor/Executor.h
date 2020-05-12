#ifndef MYNFS_EXECUTOR_H
#define MYNFS_EXECUTOR_H

#include <queue>
#include "../handlers/Handler.h"

class Executor {
    std::queue<Handler*>& messageQueue;     //TODO zaimplementować safe queue
public:
    std::mutex serverStop;

    Executor(std::queue<Handler*>& q): messageQueue(q) {}

    void run();

};


#endif //MYNFS_EXECUTOR_H
