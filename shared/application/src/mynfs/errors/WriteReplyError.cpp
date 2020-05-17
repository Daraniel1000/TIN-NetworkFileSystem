#include "application/mynfs/errors/WriteReplyError.h"

const std::unordered_map<int8_t, std::string> WriteReplyError::stringMap = {
        {0, "Success"},
        {1, "Error"} //TODO
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
