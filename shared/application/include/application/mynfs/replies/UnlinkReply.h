#ifndef MYNFS_UNLINKREPLY_H
#define MYNFS_UNLINKREPLY_H


#include "Reply.h"
#include <cstdint>
#include <session/DomainData.h>
#include <session/PlainError.h>
#include <application/mynfs/errors/UnlinkReplyError.h>


class UnlinkReply : public Reply
{
    UnlinkReplyError error;
public:
    /**
     * Create open reply from arguments (sending side)
     * @param error if error happened pass it here (other arguments are not important)
     */
    explicit UnlinkReply(UnlinkReplyError  error = UnlinkReplyError());

    /**
     * Deserialize reply (receiving side)
     * @param data reply data
     * @param error reply error
     */
    UnlinkReply(const DomainData& data, PlainError error);

    const MyNFSError & getError() const override;
    DomainData serialize() const override;

    bool operator==(const UnlinkReply &rhs) const;

    bool operator!=(const UnlinkReply &rhs) const;
};


#endif //MYNFS_UNLINKREPLY_H
