#include "application/mynfs/errors/ReadReplyError.h"

const std::unordered_map<int8_t, std::string> ReadReplyError::stringMap = {
        {0, "Success"},
        {99, "Internal server error"},
        {EBADF, "Not valid descriptor or not opened for reading"},
        {EAGAIN, "File marked as nonblocking and read would block it"},
        {EINVAL, "File is unsuitable for reading"},
        {EISDIR, "File descriptor refers to directory"}
};

ReadReplyError::ReadReplyError(int8_t errorValue) : MyNFSError(errorValue)
{
    if(errorValue == -1)
        this->errorValue = 99;
    if(stringMap.find(this->errorValue) == stringMap.end())
        throw std::logic_error("Wrong error value");
}

ReadReplyError::ReadReplyError(const PlainError &error) : MyNFSError(error)
{
    if(stringMap.find(this->errorValue) == stringMap.end())
        throw std::logic_error("Wrong error value");
}

std::string ReadReplyError::toString() const
{
    return ReadReplyError::stringMap.at(this->getErrorValue());
}
