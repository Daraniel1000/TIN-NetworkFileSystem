#ifndef MYNFS_READREPLY_H
#define MYNFS_READREPLY_H

#include "Reply.h"
#include <cstdint>
#include <session/DomainData.h>
#include <session/PlainError.h>
#include <application/mynfs/errors/ReadReplyError.h>
#include <session/Converter.h>


class ReadReply : public Reply
{
    int16_t dataSize;
    ReadReplyError error;
public:
    /**
     * Create open reply from arguments (sending side)
     * @param dataSize size of data read from file
     */
    explicit ReadReply(int16_t dataSize, ReadReplyError  error = ReadReplyError());

    /**
     * Deserialize reply (receiving side)
     * @param data reply data
     * @param error reply error
     */
    ReadReply(const DomainData& data, PlainError error);

    int16_t getDataSize() const;

    const MyNFSError & getError() const override;
    DomainData getData() const override;
};

#endif //MYNFS_READREPLY_H
