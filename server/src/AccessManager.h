#ifndef MYNFS_ACCESSMANAGER_H
#define MYNFS_ACCESSMANAGER_H


#include <cstdint>
#include <string>
#include <addresses/IpAddress.h>
#include <addresses/NetworkAddress.h>
#include <map>
#include <set>
#include <vector>

class AccessManager
{
    std::string baseDir;
    std::string fsDir;

    std::set<IpAddress> permittedHosts;
    std::map<std::pair<IpAddress, int16_t>, int> descriptorsMap;

    int high_water_mark = 0;
    std::vector<int16_t> unused_numbers;
public:
    explicit AccessManager(const std::string &baseDir, const std::string &fsDir,
                           const std::string &hostsFile);

    bool isPermitted(const IpAddress &address) const;

    int getSystemDescriptor(const IpAddress &address, int16_t appDescriptor) const;

    int16_t generateAppDescriptor(const IpAddress &address, int systemDescriptor);

    bool clearAppDescriptor(const IpAddress &address, int appDescriptor);

    bool isPathPermitted(const std::string &path) const;

    std::string getFsPath() const;
};


#endif //MYNFS_ACCESSMANAGER_H
