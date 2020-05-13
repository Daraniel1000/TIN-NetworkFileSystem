#ifndef MYNFS_SAFEQUEUE_H
#define MYNFS_SAFEQUEUE_H

#include <queue>
#include <condition_variable>

template<class Type>
class SafeQueue : private std::queue<Type>      //TODO przełożyć implementację fcji na zewnątrz jak będzie mi się chciało
{
    std::mutex mutex;
    std::condition_variable empty;
public:
    SafeQueue() : queue<Type>::queue() {};
    ~SafeQueue() : queue<Type>::~queue() {};
    SafeQueue(SafeQueue& q) : queue<Type>::queue(q) {};

    Type& frontSafe()
    {
        std::unique_lock<std::mutex> mlock(mutex);
        while(this->empty())
        {
            empty.wait(mlock);
        }
        return this->front();
    }

    Type popSafe()
    {
        std::unique_lock<std::mutex> mlock(mutex);
        while(this->empty())
        {
            empty.wait(mlock);
        }
        return this->pop();
    }

    void pushSafe(const Type& t)
    {
        std::unique_lock<std::mutex> mlock(mutex);
        this->push(t);
        mlock.unlock();
        empty.notify_one();
    }

    void pushSafe(Type&& t)
    {
        std::unique_lock<std::mutex> mlock(mutex);
        this->push(std::move(t));
        mlock.unlock();
        empty.notify_one();
    }

    const int sizeSafe()
    {
        std::unique_lock<std::mutex> mlock(mutex);
        int ret = this->size();
        mlock.unlock();
        return ret;
    }

    const bool emptySafe()
    {
        std::unique_lock<std::mutex> mlock(mutex);
        bool ret = this->queue<type>::empty();
        mlock.unlock();
        return ret;
    }

};

#endif //MYNFS_SAFEQUEUE_H
