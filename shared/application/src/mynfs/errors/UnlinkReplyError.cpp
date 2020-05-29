#include "application/mynfs/errors/UnlinkReplyError.h"

const std::unordered_map<int8_t, std::string> UnlinkReplyError::stringMap = {
        {0, "Success"},
        {99, "Internal server error"},
        {EISDIR, "Path refers to directory"},
        {EBUSY, "File can not be unlinked because it is being used"},
        {ENAMETOOLONG, "Pathname was too long"},
        {ENOENT, "A component im pathname does not exist"},
        {ENOTDIR, "A component used as a directory in pathname is not a directory"}//TODO
};

UnlinkReplyError::UnlinkReplyError(int8_t errorValue) : MyNFSError(errorValue)
{
    if(errorValue == -1)
        this->errorValue = 99;
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
