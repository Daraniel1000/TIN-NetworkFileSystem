#ifndef MYNFS_LSEEKREQUEST_H
#define MYNFS_LSEEKREQUEST_H


#include <cstdint>
#include <string>
#include "Request.h"

class LseekRequest : public Request
{
    int16_t descriptor;
    int32_t offset;
    int8_t whence;
public:
    static const uint8_t TYPE;

    /**
     * Create lseek request from arguments (sending side)
     * @param descriptor descriptor of file
     * @param offset offset in file to set
     * @param whence where to count offset from (SEEK_SET, SEEK_CUR, SEEK_END)
     */
    LseekRequest(int16_t descriptor, int32_t offset, int8_t whence);

    /**
     * Deserialize request (receiving side)
     */
    explicit LseekRequest(const DomainData& data);

    int16_t getDescriptor() const;
    int32_t getOffset() const;
    int8_t getWhence() const;

    uint8_t getType() const override;
    DomainData serialize() const override;

    bool operator==(const LseekRequest &rhs) const;

    bool operator!=(const LseekRequest &rhs) const;
};


#endif //MYNFS_LSEEKREQUEST_H
