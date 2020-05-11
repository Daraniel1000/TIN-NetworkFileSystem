#ifndef MYNFS_OPENREPLY_H
#define MYNFS_OPENREPLY_H

#include "Reply.h"
#include <cstdint>
#include <session/DomainData.h>


class OpenReply : public Reply
{
    int16_t descriptor;
public:
    OpenReply(int16_t descriptor, int8_t error = 0);
    OpenReply(DomainData data, int8_t error);

    int16_t getDescriptor();

    int8_t getError() override;
    DomainData getData() const override;
};


#endif //MYNFS_OPENREPLY_H
