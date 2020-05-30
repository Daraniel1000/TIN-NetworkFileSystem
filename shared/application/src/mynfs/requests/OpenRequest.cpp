#include <session/Converter.h>
#include <stdexcept>
#include <fcntl.h>
#include <algorithm>
#include <sstream>
#include <application/mynfs/bad_argument_error.h>
#include "application/mynfs/requests/OpenRequest.h"

const uint8_t OpenRequest::TYPE = 0;
const int16_t OpenRequest::MAX_PATH_SIZE = 4096;

void checkFlagPart(const std::vector<uint16_t> &possibleValues, uint16_t value, int errorCode, const std::string &part)
{
    if (std::find(possibleValues.begin(), possibleValues.end(), value) == possibleValues.end())
    {
        std::stringstream ss;
        for (size_t i = 0; i < possibleValues.size(); ++i)
        {
            if (i != 0)
                ss << ",";
            ss << possibleValues[i];
        }
        std::string s = ss.str();

        throw bad_argument_error(1, errorCode,
                                 "Invalid oflag value. Invalid " + part + " " + std::to_string(value) +
                                 ". Only possible values are: " + s);
    }
}

void checkOflag(uint16_t value)
{
    auto accessMode = value & O_ACCMODE;
    auto creationFlag = value & 01300;
    auto statusFlag = value & 02000;

    std::vector<uint16_t> possibleModes{O_RDONLY, O_WRONLY, O_RDWR};
    std::vector<uint16_t> possibleCreationFlags{0, O_CREAT, O_EXCL, O_TRUNC, O_CREAT | O_EXCL, O_CREAT | O_TRUNC,
                                                O_EXCL | O_TRUNC, O_CREAT | O_EXCL | O_TRUNC};
    std::vector<uint16_t> possibleStatusFlags{0, O_APPEND};

    checkFlagPart(possibleModes, accessMode, 4, "mode");
    checkFlagPart(possibleCreationFlags, creationFlag, 4, "creation flag");
    checkFlagPart(possibleStatusFlags, statusFlag, 4, "status flag");
}

OpenRequest::OpenRequest(char const *path, uint16_t oflag) : oflag(oflag)
{
    if (path == nullptr)
        throw bad_argument_error(1, 3, "Path is null");
    this->path = std::string(path);
    if (this->path.size() > OpenRequest::MAX_PATH_SIZE)
        throw bad_argument_error(1, 2,
                                 "Path is too long. Expected at most" + std::to_string(OpenRequest::MAX_PATH_SIZE) +
                                 ", but got " +
                                 std::to_string(this->path.size()));
    checkOflag(this->oflag);
}

OpenRequest::OpenRequest(const DomainData &data)
{
    auto expectedSize = sizeof(this->oflag) + sizeof(OpenRequest::MAX_PATH_SIZE);
    if (data.getSize() < expectedSize)
        throw bad_argument_error(1, 1,
                                 "Bad message size. Expected at least" + std::to_string(expectedSize) + ", but got " +
                                 std::to_string(data.getSize()));

    expectedSize += OpenRequest::MAX_PATH_SIZE;
    if (data.getSize() > expectedSize)
        throw bad_argument_error(1, 2,
                                 "Bad message size. Expected at most" + std::to_string(expectedSize) + ", but got " +
                                 std::to_string(data.getSize()));

    auto dataOffset = 0;
    //get oflag
    this->oflag = Converter::getUint16FromBytes(
            data.getNBytes(sizeof(this->oflag), dataOffset));
    dataOffset += sizeof(this->oflag);

    checkOflag(this->oflag);

    //get path length
    auto pathLength = Converter::getInt16FromBytes(
            data.getNBytes(sizeof(OpenRequest::MAX_PATH_SIZE), dataOffset));
    dataOffset += sizeof(pathLength);

    //get path
    auto pathBytes = data.getNBytes(pathLength, dataOffset);
    auto charPathPtr = static_cast<char *>(static_cast<void *>(pathBytes.data()));
    this->path = std::string(charPathPtr, charPathPtr + pathBytes.size());
}

const std::string &OpenRequest::getPath() const
{
    return this->path;
}

uint16_t OpenRequest::getOflag() const
{
    return this->oflag;
}

uint8_t OpenRequest::getType() const
{
    return OpenRequest::TYPE;
}

DomainData OpenRequest::serialize() const
{
    // convert oflag
    std::vector<std::byte> dataBytes = Converter::getBytesFromUint16(this->oflag);

    // convert path length
    auto pathLengthBytes = Converter::getBytesFromInt16(this->path.size());
    dataBytes.insert(dataBytes.end(), pathLengthBytes.begin(), pathLengthBytes.end());

    // convert path
    auto charPathPtr = static_cast<const std::byte *>(static_cast<const void *>(this->path.data()));
    dataBytes.insert(dataBytes.end(), charPathPtr, charPathPtr + this->path.size());

    return DomainData(dataBytes);
}

bool OpenRequest::operator==(const OpenRequest &rhs) const
{
    return path == rhs.path &&
           oflag == rhs.oflag;
}

bool OpenRequest::operator!=(const OpenRequest &rhs) const
{
    return !(rhs == *this);
}
