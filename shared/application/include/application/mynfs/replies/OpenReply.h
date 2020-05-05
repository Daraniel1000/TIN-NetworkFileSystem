#ifndef MYNFS_OPENREPLY_H
#define MYNFS_OPENREPLY_H

#include "Reply.h"
#include <cstdint>
#include <session/DomainData.h>


class OpenReply : public Reply
{
    int16_t descriptor;
public:
    OpenReply(DomainData data);

    int16_t getDescriptor();

    int8_t getError() override;
};


#endif //MYNFS_OPENREPLY_H
