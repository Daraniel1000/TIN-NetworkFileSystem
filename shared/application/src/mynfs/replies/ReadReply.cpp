#include "application/mynfs/replies/ReadReply.h"

#include <session/Converter.h>
#include <application/mynfs/replies/ReadReply.h>


ReadReply::ReadReply(int16_t dataSize, ReadReplyError error)
{

}


ReadReply::ReadReply(const DomainData &data, PlainError error)  : error(error)
{

}

int16_t ReadReply::getDataSize() const
{
    return this->dataSize;
}

const MyNFSError &ReadReply::getError() const
{
    return this->error;
}

DomainData ReadReply::getData() const
{
    std::vector<std::byte> dataBytes = Converter::getBytesFromInt16(this->dataSize);
    return DomainData(dataBytes);
}