#include <stdexcept>
#include <session/Converter.h>
#include <application/mynfs/bad_argument_error.h>
#include "application/mynfs/requests/UnlinkRequest.h"

const uint8_t UnlinkRequest::TYPE = 5;
const int16_t UnlinkRequest::MAX_PATH_SIZE = 4096;

UnlinkRequest::UnlinkRequest(char const *path) : path(path)
{
    if(path == nullptr)
        throw bad_argument_error(1, 3, "Path is null");
    this->path = std::string(path);
    if (this->path.size() > UnlinkRequest::MAX_PATH_SIZE)
        throw bad_argument_error(1, 2,
                "Path is too long. Expected at most" + std::to_string(UnlinkRequest::MAX_PATH_SIZE) + ", but got " +
                std::to_string(this->path.size()));
}

UnlinkRequest::UnlinkRequest(const DomainData &data)
{
    auto expectedSize = sizeof(UnlinkRequest::MAX_PATH_SIZE);
    if (data.getSize() < expectedSize)
        throw bad_argument_error(1, 1,
                "Bad message size. Expected at least" + std::to_string(expectedSize) + ", but got " +
                std::to_string(data.getSize()));

    expectedSize += UnlinkRequest::MAX_PATH_SIZE;
    if (data.getSize() > expectedSize)
        throw bad_argument_error(1, 2,
                "Bad message size. Expected at most" + std::to_string(expectedSize) + ", but got " +
                std::to_string(data.getSize()));

    auto dataOffset = 0;

    //get path length
    auto pathLength = Converter::getInt16FromBytes(
            data.getNBytes(sizeof(UnlinkRequest::MAX_PATH_SIZE), dataOffset));
    dataOffset += sizeof(pathLength);

    //get path
    auto pathBytes = data.getNBytes(pathLength, dataOffset);
    auto charPathPtr = static_cast<char *>(static_cast<void *>(pathBytes.data()));
    this->path = std::string(charPathPtr, charPathPtr + pathBytes.size());
}

const std::string &UnlinkRequest::getPath() const
{
    return this->path;
}

uint8_t UnlinkRequest::getType() const
{
    return UnlinkRequest::TYPE;
}

DomainData UnlinkRequest::serialize() const
{
    // convert path length
    std::vector<std::byte> dataBytes = Converter::getBytesFromUint16(this->path.size());

    // convert path
    auto charPathPtr = static_cast<const std::byte *>(static_cast<const void *>(this->path.data()));
    dataBytes.insert(dataBytes.end(), charPathPtr, charPathPtr + this->path.size());

    return DomainData(dataBytes);
}

bool UnlinkRequest::operator==(const UnlinkRequest &rhs) const
{
    return path == rhs.path;
}

bool UnlinkRequest::operator!=(const UnlinkRequest &rhs) const
{
    return !(rhs == *this);
}
