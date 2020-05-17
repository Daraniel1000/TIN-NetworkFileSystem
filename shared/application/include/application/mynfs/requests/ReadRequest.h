#ifndef MYNFS_READREQUEST_H
#define MYNFS_READREQUEST_H


#include <cstdint>
#include <string>
#include "Request.h"

class ReadRequest : public Request
{
    int16_t descriptor;
    int16_t count;
public:
    static const uint8_t TYPE;

    /**
     * Create read request from arguments (sending side)
     * @param descriptor descriptor of file
     * @param count how many bytes to read
     */
    ReadRequest(int16_t descriptor, int16_t count);

    /**
     * Deserialize request (receiving side)
     */
    explicit ReadRequest(const DomainData& data);

    int16_t getDescriptor() const;
    int16_t getCount() const;

    uint8_t getType() const override;
    DomainData serialize() const override;

    bool operator==(const ReadRequest &rhs) const;

    bool operator!=(const ReadRequest &rhs) const;
};

#endif //MYNFS_READREQUEST_H
