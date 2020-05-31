#include <fstream>
#include "AccessManager.h"
#include <addresses/IpAddress.h>
#include <algorithm>

const std::string AccessManager::DEFAULT_HOST_FILE = "hosts.txt";

std::set<IpAddress> readPermittedHosts(const std::string& hostsPath)
{
    std::ifstream fileStream(hostsPath.c_str());

    if(!fileStream)
        throw std::runtime_error("Can't open hosts file at " + hostsPath);

    std::set<IpAddress> hosts;
    std::string str;
    while (std::getline(fileStream, str))
    {
        if(!str.empty())
            hosts.emplace(str.c_str());
    }

    fileStream.close();
    return hosts;
}

AccessManager::AccessManager(const std::string& baseDir, const std::string& hostsFile)
{
    auto fullHostsPath = baseDir + "/" + hostsFile;

    this->permittedHosts = readPermittedHosts(fullHostsPath);
}

bool AccessManager::isPermitted(const IpAddress &address) const
{
    return this->permittedHosts.find(address) != this->permittedHosts.end();
}

int16_t AccessManager::getDescriptor(const NetworkAddress &address) const
{
    auto it = this->descriptorsMap.find(address);
    if (it == this->descriptorsMap.end())
        return -1;
    return it->second;
}

int16_t AccessManager::generateDescriptor(const NetworkAddress &address)
{
    auto it = this->descriptorsMap.find(address);
    if (it != this->descriptorsMap.end())
        return it->second;

    int16_t descriptor;
    if (this->unused_numbers.empty())
        descriptor = high_water_mark++;
    else
    {
        std::pop_heap(unused_numbers.begin(), unused_numbers.end(), std::greater<>());
        descriptor = this->unused_numbers.back();
        this->unused_numbers.pop_back();
    }
    this->descriptorsMap.emplace(address, descriptor);
    return descriptor;
}

bool AccessManager::clearDescriptor(const NetworkAddress &address)
{
    auto it = this->descriptorsMap.find(address);
    if (it == this->descriptorsMap.end())
        return false;
    unused_numbers.push_back(it->second);
    std::push_heap(unused_numbers.begin(), unused_numbers.end(), std::greater<>());
    this->descriptorsMap.erase(it);
    return true;
}
