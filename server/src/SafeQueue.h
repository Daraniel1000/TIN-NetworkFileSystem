#ifndef MYNFS_SAFEQUEUE_H
#define MYNFS_SAFEQUEUE_H

#include <queue>
#include <condition_variable>

template<class Type>
class SafeQueue : private std::queue<Type>
{
    std::mutex mutex;
    std::condition_variable isEmpty;
    int size = 0;
public:
    SafeQueue() : std::queue<Type>::queue() {};
    SafeQueue(SafeQueue& q) : std::queue<Type>::queue(q) {};

    Type frontSafe()
    {
        std::unique_lock<std::mutex> mlock(mutex);
        if(size==0)
        {
            isEmpty.wait(mlock);
        }
        if(size==0) return nullptr;
        return this->front();
    }

    void popSafe()
    {
        std::unique_lock<std::mutex> mlock(mutex);
        while(size==0)
        {
            isEmpty.wait(mlock);
        }
        --size;
        this->pop();
    }

    void pushSafe(const Type& t)
    {
        std::unique_lock<std::mutex> mlock(mutex);
        this->push(t);
        ++size;
        mlock.unlock();
        isEmpty.notify_one();
    }

    void pushSafe(Type&& t)
    {
        std::unique_lock<std::mutex> mlock(mutex);
        this->push(std::move(t));
        ++size;
        mlock.unlock();
        isEmpty.notify_one();
    }

    const int sizeSafe()
    {
        std::unique_lock<std::mutex> mlock(mutex);
        int ret = size;
        mlock.unlock();
        return ret;
    }

    const bool emptySafe()
    {
        std::unique_lock<std::mutex> mlock(mutex);
        bool ret = (size==0);
        mlock.unlock();
        return ret;
    }

    const void notify()
    {
        isEmpty.notify_all();
    }

};


#endif //MYNFS_SAFEQUEUE_H
