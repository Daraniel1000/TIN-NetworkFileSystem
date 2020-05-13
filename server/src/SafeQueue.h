#ifndef MYNFS_SAFEQUEUE_H
#define MYNFS_SAFEQUEUE_H

#include <queue>
#include <condition_variable>

template<class Type>
class SafeQueue : private std::queue<Type>      //TODO przełożyć implementację fcji na zewnątrz jak będzie mi się chciało
{
    std::mutex mutex;
    std::condition_variable isEmpty;
public:
    SafeQueue() : std::queue<Type>::queue() {};
    SafeQueue(SafeQueue& q) : std::queue<Type>::queue(q) {};

    Type& frontSafe()
    {
        std::unique_lock<std::mutex> mlock(mutex);
        while(this->empty())
        {
            isEmpty.wait(mlock);
        }
        return this->front();
    }

    void popSafe()
    {
        std::unique_lock<std::mutex> mlock(mutex);
        while(this->empty())
        {
            isEmpty.wait(mlock);
        }
        this->pop();
    }

    void pushSafe(const Type& t)
    {
        std::unique_lock<std::mutex> mlock(mutex);
        this->push(t);
        mlock.unlock();
        isEmpty.notify_one();
    }

    void pushSafe(Type&& t)
    {
        std::unique_lock<std::mutex> mlock(mutex);
        this->push(std::move(t));
        mlock.unlock();
        isEmpty.notify_one();
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
        bool ret = this->empty();
        mlock.unlock();
        return ret;
    }

};

#endif //MYNFS_SAFEQUEUE_H
