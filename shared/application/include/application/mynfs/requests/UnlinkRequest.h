#ifndef MYNFS_UNLINKREQUEST_H
#define MYNFS_UNLINKREQUEST_H


#include <cstdint>
#include <string>
#include "Request.h"

class UnlinkRequest : public Request
{
    std::string path;
public:
    static const uint8_t TYPE;
    static const int16_t MAX_PATH_SIZE;

    /**
     * Create unlink request from arguments (sending side)
     * @param path path to the file
     */
    UnlinkRequest(char const *path);

    /**
     * Deserialize request (receiving side)
     */
    explicit UnlinkRequest(const DomainData& data);

    const std::string& getPath() const;

    uint8_t getType() const override;
    DomainData serialize() const override;
};


#endif //MYNFS_UNLINKREQUEST_H
