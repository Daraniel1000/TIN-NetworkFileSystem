#ifndef MYNFS_HANDLER_H
#define MYNFS_HANDLER_H


#include <cstdint>
#include <session/DomainData.h>
#include <condition_variable>
#include <session/PlainError.h>

class Handler
{
protected:
    DomainData requestData;
    DomainData &replyData;
    PlainError &replyError;
public:
    std::mutex m;
    std::condition_variable cv;
    /**
     * Construct handler
     * @param requestData data of request
     * @param replyData reference to reply data (it will be overridden)
     * @param replyError reference to reply error (it will be overridden)
     */
    Handler(DomainData requestData, DomainData &replyData, PlainError &replyError) : requestData(requestData),
                                                                                     replyData(replyData),
                                                                                     replyError(replyError)
    {}

    virtual ~Handler() {};

    /**
     * Main handler function, operate on request and fill reply (or error) according to handler logic
     */
    virtual void handle() = 0;

    void waitForCompletion()
    {
        std::unique_lock<std::mutex> lk(this->m);
        this->cv.wait(lk);   //wait_for żeby ustawić timeout wykonania
    }

    void signalCompletion()
    {
        std::lock_guard<std::mutex> lk(this->m);
        this->cv.notify_all();
    }
};


#endif //MYNFS_HANDLER_H
