#include "application/mynfs/errors/OpenReplyError.h"

const std::unordered_map<int8_t, std::string> OpenReplyError::stringMap = {
        {0, "Success"},
        {1, "Error"},
        {2, "No file"}//TODO
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


std::string OpenReplyError::toString() const
{
    return OpenReplyError::stringMap.at(this->getErrorValue());
}