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
    static const std::string DEFAULT_HOST_FILE;

    std::set<IpAddress> permittedHosts;
    std::map<NetworkAddress, int16_t> descriptorsMap;

    int high_water_mark = 0;
    std::vector<int16_t> unused_numbers;
public:
    explicit AccessManager(const std::string& baseDir, const std::string& hostsFile = DEFAULT_HOST_FILE);

    bool isPermitted(const IpAddress& address) const;
    int16_t getDescriptor(const NetworkAddress& address) const;

    int16_t generateDescriptor(const NetworkAddress& address);
    bool clearDescriptor(const NetworkAddress& address);
};


#endif //MYNFS_ACCESSMANAGER_H
