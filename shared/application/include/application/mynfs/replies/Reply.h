#ifndef MYNFS_REPLY_H
#define MYNFS_REPLY_H

#include <cstdint>
#include <session/DomainData.h>

class Reply
{
    int8_t error;
public:
    /**
     * Create base reply
     * @param error (0 = no error)
     */
    Reply(int8_t error) : error(error) {}
    virtual ~Reply() = default;

    /**
     * Get reply error (0 = no erro)
     */
    virtual int8_t getError() = 0;

    /**
     * Serialize reply object to plain data
     */
    virtual DomainData getData() const = 0;
};


#endif //MYNFS_REPLY_H
