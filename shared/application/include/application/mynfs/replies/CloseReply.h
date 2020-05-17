#ifndef MYNFS_CLOSEREPLY_H
#define MYNFS_CLOSEREPLY_H


#include "Reply.h"
#include <cstdint>
#include <session/DomainData.h>
#include <session/PlainError.h>
#include <application/mynfs/errors/CloseReplyError.h>


class CloseReply : public Reply
{
    CloseReplyError error;
public:
    /**
     * Create close reply from arguments (sending side)
     * @param error if error happened pass it here (other arguments are not important)
     */
    explicit CloseReply(CloseReplyError  error = CloseReplyError());

    /**
     * Deserialize reply (receiving side)
     * @param data reply data
     * @param error reply error
     */
    CloseReply(const DomainData& data, PlainError error);

    const MyNFSError & getError() const override;
    DomainData serialize() const override;
};


#endif //MYNFS_CLOSEREPLY_H
