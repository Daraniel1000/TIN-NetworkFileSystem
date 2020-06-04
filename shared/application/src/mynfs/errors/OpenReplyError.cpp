#include "application/mynfs/errors/OpenReplyError.h"

const std::unordered_map<int8_t, std::string> OpenReplyError::stringMap = {
        {0, "Success"},
        {99, "Internal server error"},
        {EACCES, "Permission denied"},
        {EEXIST, "O_CREAT and O_EXCL are set but file exists"},
        {ELOOP, "A loop exists in symbolic links encountered during resolution of the path"},
        {ENAMETOOLONG, "Path is too long or pathname component is too long"},
        {ENFILE, "Too much files are open in the system"},
        {ENOENT, "File does not exist"},
        {ENOSPC, "A file can not be created in specify localization and O_CREAT is set"},
        {ENOTDIR, "A component of the path prefix is not a directory"},
        {EINVAL, "The value of the flag argument is not valid"}
};

OpenReplyError::OpenReplyError(int8_t errorValue) : MyNFSError(errorValue)
{
    if(errorValue == -1)
        this->errorValue = 99;
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