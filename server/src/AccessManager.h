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
    std::map<std::pair<NetworkAddress, int16_t>, int> descriptorsMap;

    int high_water_mark = 0;
    std::vector<int16_t> unused_numbers;
public:
    explicit AccessManager(const std::string& baseDir, const std::string& hostsFile = DEFAULT_HOST_FILE);

    bool isPermitted(const IpAddress& address) const;
    int getSystemDescriptor(const NetworkAddress& address, int16_t appDescriptor) const;

    int16_t generateAppDescriptor(const NetworkAddress& address, int systemDescriptor);
    bool clearAppDescriptor(const NetworkAddress& address, int appDescriptor);
};


#endif //MYNFS_ACCESSMANAGER_H
