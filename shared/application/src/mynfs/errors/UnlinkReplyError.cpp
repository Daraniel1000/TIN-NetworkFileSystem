#include "application/mynfs/errors/UnlinkReplyError.h"

const std::unordered_map<int8_t, std::string> UnlinkReplyError::stringMap = {
        {0, "Success"},
        {1, "Error"} //TODO
};

UnlinkReplyError::UnlinkReplyError(int8_t errorValue) : MyNFSError(errorValue)
{
    if(stringMap.find(this->errorValue) == stringMap.end())
        throw std::logic_error("Wrong error value");
}

UnlinkReplyError::UnlinkReplyError(const PlainError &error) : MyNFSError(error)
{
    if(stringMap.find(this->errorValue) == stringMap.end())
        throw std::logic_error("Wrong error value");
}

std::string UnlinkReplyError::toString() const
{
    return UnlinkReplyError::stringMap.at(this->getErrorValue());
}
