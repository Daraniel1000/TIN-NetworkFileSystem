#ifndef MYNFS_WRITEREQUEST_H
#define MYNFS_WRITEREQUEST_H


#include <cstdint>
#include <string>
#include "Request.h"

class WriteRequest : public Request
{
    int16_t descriptor;
    PlainData writeData;
public:
    static const uint8_t TYPE;

    /**
     * Create write request from arguments (sending side)
     * @param descriptor descriptor of file
     * @param buf buffer with data to write
     * @param count buffer size
     */
    WriteRequest(int16_t descriptor, void* buf, int16_t count);

    /**
     * Deserialize request (receiving side)
     */
    explicit WriteRequest(const DomainData& data);

    int16_t getDescriptor() const;
    const PlainData& getWriteData() const;

    uint8_t getType() const override;
    DomainData serialize() const override;
};


#endif //MYNFS_WRITEREQUEST_H
