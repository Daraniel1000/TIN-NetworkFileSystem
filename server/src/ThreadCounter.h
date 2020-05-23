#ifndef MYNFS_THREADCOUNTER_H
#define MYNFS_THREADCOUNTER_H

#include <condition_variable>

class ThreadCounter{
    std::mutex mutex;
    std::condition_variable boi;
    int n;
public:

    void await()
    {
        std::unique_lock<std::mutex> mlock(mutex);
        if(n>0)
        {
            boi.wait(mlock);
        }
    }

    int enter()
    {
        std::unique_lock<std::mutex> mlock(mutex);
        ++n;
        return n;
    }

    int leave()
    {
        std::unique_lock<std::mutex> mlock(mutex);
        --n;
        if(n<=0) boi.notify_all();
        return n;
    }
};

#endif //MYNFS_THREADCOUNTER_H
