#ifndef MYNFS_READREPLY_H
#define MYNFS_READREPLY_H


#include "Reply.h"
#include <cstdint>
#include <session/DomainData.h>
#include <session/PlainError.h>
#include <application/mynfs/errors/ReadReplyError.h>


class ReadReply : public Reply
{
    PlainData readData;
    ReadReplyError error;
public:
    /**
     * Create read reply from arguments (sending side)
     * @param buf buffer with data
     * @param count size of buffer
     * @param error if error happened pass it here (other arguments are not important)
     */
    explicit ReadReply(void* buf, int16_t count, ReadReplyError  error = ReadReplyError());

    /**
     * Deserialize reply (receiving side)
     * @param data reply data
     * @param error reply error
     */
    ReadReply(const DomainData& data, PlainError error);

    const PlainData& getData() const;

    const MyNFSError & getError() const override;
    DomainData serialize() const override;
};


#endif //MYNFS_READREPLY_H
