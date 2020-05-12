#ifndef MYNFS_HANDLER_H
#define MYNFS_HANDLER_H


#include <cstdint>
#include <session/DomainData.h>
#include <condition_variable>

class Handler
{
    DomainData requestData;
    DomainData &replyData;
    int8_t &replyError;
public:
    std::mutex m;
    std::condition_variable cv;
    /**
     * Construct handler
     * @param requestData data of request
     * @param replyData reference to reply data (it will be overridden)
     * @param replyError reference to reply error (it will be overridden)
     */
    Handler(DomainData requestData, DomainData &replyData, int8_t &replyError) : requestData(requestData),
                                                                                 replyData(replyData),
                                                                                 replyError(replyError)
    {}

    virtual ~Handler() = default;

    /**
     * Main handler function, operate on request and fill reply (or error) according to handler logic
     * must end with:
     * std::lock_guard<std::mutex> lk(m);
     * cv.notify_all();
     */
    virtual void handle() = 0;

    void fail();
};


#endif //MYNFS_HANDLER_H
