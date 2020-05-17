#ifndef MYNFS_OPENREQUEST_H
#define MYNFS_OPENREQUEST_H


#include <cstdint>
#include <string>
#include "Request.h"

class OpenRequest : public Request
{
    std::string path;
    uint16_t oflag;
public:
    static const uint8_t TYPE;
    static const int16_t MAX_PATH_SIZE;

    /**
     * Create open request from arguments (sending side)
     * @param path path to the file
     * @param oflag open flags
     */
    OpenRequest(char const *path, uint16_t oflag);

    /**
     * Deserialize request (receiving side)
     */
    explicit OpenRequest(const DomainData& data);

    const std::string& getPath() const;
    uint16_t getOflag() const;

    uint8_t getType() const override;
    DomainData serialize() const override;
};


#endif //MYNFS_OPENREQUEST_H
