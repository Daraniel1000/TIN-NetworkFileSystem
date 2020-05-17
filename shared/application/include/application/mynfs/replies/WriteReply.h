#ifndef MYNFS_WRITEREPLY_H
#define MYNFS_WRITEREPLY_H


#include "Reply.h"
#include <cstdint>
#include <session/DomainData.h>
#include <session/PlainError.h>
#include <application/mynfs/errors/WriteReplyError.h>


class WriteReply : public Reply
{
    int16_t count;
    WriteReplyError error;
public:
    /**
     * Create write reply from arguments (sending side)
     * @param count number of bytes written
     * @param error if error happened pass it here (other arguments are not important)
     */
    explicit WriteReply(int16_t count, WriteReplyError  error = WriteReplyError());

    /**
     * Deserialize reply (receiving side)
     * @param data reply data
     * @param error reply error
     */
    WriteReply(const DomainData& data, PlainError error);

    int16_t getCount() const;

    const MyNFSError & getError() const override;
    DomainData serialize() const override;
};


#endif //MYNFS_WRITEREPLY_H
