#include "application/mynfs/errors/CloseReplyError.h"

const std::unordered_map<int8_t, std::string> CloseReplyError::stringMap = {
        {0, "Success"},
        {99, "Internal server error"},
        {EBADF, "Not valid descriptor"}
};

CloseReplyError::CloseReplyError(int8_t errorValue) : MyNFSError(errorValue)
{
    if(errorValue == -1)
        this->errorValue = 99;
    if(stringMap.find(this->errorValue) == stringMap.end())
        throw std::logic_error("Wrong error value");
}

CloseReplyError::CloseReplyError(const PlainError &error) : MyNFSError(error)
{
    if(stringMap.find(this->errorValue) == stringMap.end())
        throw std::logic_error("Wrong error value");
}

std::string CloseReplyError::toString() const
{
    return CloseReplyError::stringMap.at(this->getErrorValue());
}
