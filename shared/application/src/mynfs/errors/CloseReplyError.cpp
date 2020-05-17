#include "application/mynfs/errors/CloseReplyError.h"

CloseReplyError::CloseReplyError(int8_t errorValue) : MyNFSError(errorValue)
{

}

CloseReplyError::CloseReplyError(const PlainError &error) : MyNFSError(error)
{

}

std::string CloseReplyError::toString() const
{
    return std::string();
}
