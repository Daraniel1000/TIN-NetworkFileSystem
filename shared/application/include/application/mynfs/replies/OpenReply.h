#ifndef MYNFS_OPENREPLY_H
#define MYNFS_OPENREPLY_H

#include "Reply.h"
#include <cstdint>
#include <session/DomainData.h>
#include <session/PlainError.h>
#include <application/mynfs/errors/OpenReplyError.h>


class OpenReply : public Reply
{
    int16_t descriptor;
    OpenReplyError error;
public:
    /**
     * Create open reply from arguments (sending side)
     * @param descriptor descriptor of opened file
     * @param error if error happened pass it here (other arguments are not important)
     */
    explicit OpenReply(int16_t descriptor, OpenReplyError  error = OpenReplyError());

    /**
     * Deserialize reply (receiving side)
     * @param data reply data
     * @param error reply error
     */
    OpenReply(const DomainData& data, PlainError error);

    int16_t getDescriptor() const;

    const MyNFSError & getError() const override;
    DomainData serialize() const override;
};


#endif //MYNFS_OPENREPLY_H
