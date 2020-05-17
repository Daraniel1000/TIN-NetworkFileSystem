#include "application/mynfs/errors/ReadReplyError.h"

ReadReplyError::ReadReplyError(int8_t errorValue) : MyNFSError(errorValue)
{

}

ReadReplyError::ReadReplyError(const PlainError &error) : MyNFSError(error)
{

}

std::string ReadReplyError::toString() const
{
    return std::string();
}
