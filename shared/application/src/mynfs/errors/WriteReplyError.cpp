#include "application/mynfs/errors/WriteReplyError.h"

WriteReplyError::WriteReplyError(int8_t errorValue) : MyNFSError(errorValue)
{

}

WriteReplyError::WriteReplyError(const PlainError &error) : MyNFSError(error)
{

}

std::string WriteReplyError::toString() const
{
    return std::string();
}
