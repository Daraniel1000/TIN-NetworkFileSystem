#include "application/mynfs/errors/OpenReplyError.h"

const std::unordered_map<int8_t, std::string> OpenReplyError::stringMap = {
        {0, "Success"}
};

OpenReplyError::OpenReplyError(int8_t errorValue) : MyNFSError(errorValue)
{
    if(stringMap.find(this->errorValue) == stringMap.end())
        throw std::logic_error("Wrong error value");
}

OpenReplyError::OpenReplyError(const PlainError &error) : MyNFSError(error)
{
    if(stringMap.find(this->errorValue) == stringMap.end())
        throw std::logic_error("Wrong error value");
}


std::string OpenReplyError::toString()
{
    return OpenReplyError::stringMap.at(this->getErrorValue());
}