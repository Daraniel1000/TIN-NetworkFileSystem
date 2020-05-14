#ifndef MYNFS_REPLY_H
#define MYNFS_REPLY_H

#include <cstdint>
#include <session/DomainData.h>
#include <application/mynfs/errors/MyNFSError.h>

class Reply
{
public:
    virtual ~Reply() = default;

    /**
     * Get reply error (0 = no erro)
     */
    virtual const MyNFSError& getError() = 0;

    /**
     * Serialize reply object to plain data
     */
    virtual DomainData getData() const = 0;
};


#endif //MYNFS_REPLY_H
