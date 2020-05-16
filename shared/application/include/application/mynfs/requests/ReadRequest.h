#ifndef MYNFS_READREQUEST_H
#define MYNFS_READREQUEST_H

#include <cstdint>
#include <string>
#include "Request.h"

class ReadRequest : public Request
{
    int16_t fd;
    void *buf;
    int16_t count;

public:
    static const int16_t MAX_BUF_SIZE = 4096;

    /**
     * Create open request from arguments (sending side)
     * @param fd file descriptor
     * @param buf buffer for read data
     * @param count data size to read
     */
    ReadRequest(int16_t fd, void *buf, int16_t count);

    /**
     * Deserialize request (receiving side)
     */
    explicit ReadRequest(const DomainData& data);

    int16_t getFileDescriptor();
    void * getBuf() const;
    int16_t getCount();

    uint8_t getType() const override;
    DomainData getData() const override;
};

#endif //MYNFS_READREQUEST_H
