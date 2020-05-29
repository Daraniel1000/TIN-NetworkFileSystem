#include "application/mynfs/errors/LseekReplyError.h"

const std::unordered_map<int8_t, std::string> LseekReplyError::stringMap = {
        {0, "Success"},
        {99, "Internal Server error"},
        {EBADF, "Not valid descriptor"},
        {EINVAL, "Not valid whence or result offset would be negative"}//TODO
};

LseekReplyError::LseekReplyError(int8_t errorValue) : MyNFSError(errorValue)
{
    if(errorValue == -1)
        this->errorValue = 99;
    if(stringMap.find(this->errorValue) == stringMap.end())
        throw std::logic_error("Wrong error value");
}

LseekReplyError::LseekReplyError(const PlainError &error) : MyNFSError(error)
{
    if(stringMap.find(this->errorValue) == stringMap.end())
        throw std::logic_error("Wrong error value");
}

std::string LseekReplyError::toString() const
{
    return LseekReplyError::stringMap.at(this->getErrorValue());
}
