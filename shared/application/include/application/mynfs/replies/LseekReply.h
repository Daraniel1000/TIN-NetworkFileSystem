#ifndef MYNFS_LSEEKREPLY_H
#define MYNFS_LSEEKREPLY_H


#include "Reply.h"
#include <cstdint>
#include <session/DomainData.h>
#include <session/PlainError.h>
#include <application/mynfs/errors/LseekReplyError.h>


class LseekReply : public Reply
{
    int32_t offset;
    LseekReplyError error;
public:
    /**
     * Create lseek reply from arguments (sending side)
     * @param offset set offset
     * @param error if error happened pass it here (other arguments are not important)
     */
    explicit LseekReply(int32_t offset, LseekReplyError  error = LseekReplyError());

    /**
     * Deserialize reply (receiving side)
     * @param data reply data
     * @param error reply error
     */
    LseekReply(const DomainData& data, PlainError error);

    int32_t getOffset() const;

    const MyNFSError & getError() const override;
    DomainData serialize() const override;

    bool operator==(const LseekReply &rhs) const;

    bool operator!=(const LseekReply &rhs) const;
};


#endif //MYNFS_LSEEKREPLY_H
