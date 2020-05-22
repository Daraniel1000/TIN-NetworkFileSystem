#include "application/mynfs/errors/LseekReplyError.h"

const std::unordered_map<int8_t, std::string> LseekReplyError::stringMap = {
        {0, "Success"},
        {1, "Error"},
        {EBADF, "Not valid descriptor"}//TODO
};

LseekReplyError::LseekReplyError(int8_t errorValue) : MyNFSError(errorValue)
{
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
