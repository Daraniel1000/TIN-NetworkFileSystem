#include "application/mynfs/errors/UnlinkReplyError.h"

UnlinkReplyError::UnlinkReplyError(int8_t errorValue) : MyNFSError(errorValue)
{

}

UnlinkReplyError::UnlinkReplyError(const PlainError &error) : MyNFSError(error)
{

}

std::string UnlinkReplyError::toString() const
{
    return std::string();
}
