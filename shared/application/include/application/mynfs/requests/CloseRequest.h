#ifndef MYNFS_CLOSEREQUEST_H
#define MYNFS_CLOSEREQUEST_H


#include <cstdint>
#include <string>
#include "Request.h"

class CloseRequest : public Request
{
    int16_t descriptor;
public:
    static const uint8_t TYPE;

    /**
     * Create close request from arguments (sending side)
     * @param descriptor descriptor of file
     */
    CloseRequest(int16_t descriptor);

    /**
     * Deserialize request (receiving side)
     */
    explicit CloseRequest(const DomainData& data);

    int16_t getDescriptor() const;

    uint8_t getType() const override;
    DomainData serialize() const override;
};

#endif //MYNFS_CLOSEREQUEST_H
