#include "application/mynfs/errors/LseekReplyError.h"

LseekReplyError::LseekReplyError(int8_t errorValue) : MyNFSError(errorValue)
{

}

LseekReplyError::LseekReplyError(const PlainError &error) : MyNFSError(error)
{

}

std::string LseekReplyError::toString() const
{
    return std::string();
}
