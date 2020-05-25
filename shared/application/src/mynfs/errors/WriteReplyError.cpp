#include "application/mynfs/errors/WriteReplyError.h"

const std::unordered_map<int8_t, std::string> WriteReplyError::stringMap = {
        {0, "Success"},
        {-1, "Internal server error"},
        {EBADF, "Not valid descriptor or not open for writing"},
        {EAGAIN, "File marked as nonblocking and write would block it"},
        {EFBIG, "Write at the position past the maximum allowed offset"},
        {EINVAL, "File descriptor is attached to an object which is unsuitable for writing"}//TODO
};

WriteReplyError::WriteReplyError(int8_t errorValue) : MyNFSError(errorValue)
{
    if(stringMap.find(this->errorValue) == stringMap.end())
        throw std::logic_error("Wrong error value");
}

WriteReplyError::WriteReplyError(const PlainError &error) : MyNFSError(error)
{
    if(stringMap.find(this->errorValue) == stringMap.end())
        throw std::logic_error("Wrong error value");
}

std::string WriteReplyError::toString() const
{
    return WriteReplyError::stringMap.at(this->getErrorValue());
}
