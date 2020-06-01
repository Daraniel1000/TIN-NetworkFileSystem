#include <fstream>
#include "AccessManager.h"
#include <addresses/IpAddress.h>
#include <algorithm>
#include <sys/stat.h>

std::set<IpAddress> readPermittedHosts(const std::string &hostsPath)
{
    std::fstream fileStream(hostsPath.c_str(), std::fstream::in | std::fstream::app);

    if (!fileStream)
        throw std::runtime_error("Can't open hosts file at " + hostsPath);

    std::set<IpAddress> hosts;
    std::string str;
    while (std::getline(fileStream, str))
    {
        if (!str.empty())
            hosts.emplace(str.c_str());
    }

    fileStream.close();
    return hosts;
}

AccessManager::AccessManager(const std::string &baseDir, const std::string &fsDir, const std::string &hostsFile)
        : baseDir(baseDir), fsDir(fsDir)
{
    auto fullHostsPath = baseDir + "/" + hostsFile;

    mkdir(baseDir.c_str(), 0777);
    std::string fsPath = this->getFsPath();
    mkdir(fsPath.c_str(), 0777);

    this->permittedHosts = readPermittedHosts(fullHostsPath);
}

bool AccessManager::isPermitted(const IpAddress &address) const
{
    return this->permittedHosts.find(address) != this->permittedHosts.end();
}

int AccessManager::getSystemDescriptor(const IpAddress &address, int16_t appDescriptor) const
{
    auto it = this->descriptorsMap.find(std::make_pair(address, appDescriptor));
    if (it == this->descriptorsMap.end())
        return -1;
    return it->second;
}

int16_t AccessManager::generateAppDescriptor(const IpAddress &address, int systemDescriptor)
{
    auto it = std::find_if(
            this->descriptorsMap.begin(),
            this->descriptorsMap.end(),
            [&](const auto &kv) { return kv.first.first == address and kv.second == systemDescriptor; });
    if (it != this->descriptorsMap.end())
        return it->first.second;

    int16_t appDescriptor;
    if (this->unused_numbers.empty())
        appDescriptor = high_water_mark++;
    else
    {
        std::pop_heap(unused_numbers.begin(), unused_numbers.end(), std::greater<>());
        appDescriptor = this->unused_numbers.back();
        this->unused_numbers.pop_back();
    }
    this->descriptorsMap.emplace(std::make_pair(address, appDescriptor), systemDescriptor);
    return appDescriptor;
}

bool AccessManager::clearAppDescriptor(const IpAddress &address, int appDescriptor)
{
    auto it = this->descriptorsMap.find(std::make_pair(address, appDescriptor));
    if (it == this->descriptorsMap.end())
        return false;
    unused_numbers.push_back(appDescriptor);
    std::push_heap(unused_numbers.begin(), unused_numbers.end(), std::greater<>());
    this->descriptorsMap.erase(it);
    return true;
}

bool AccessManager::isPathPermitted(const std::string &path) const
{
    return (this->getFsPath() + "/" + path).find("..") == std::string::npos;
}

std::string AccessManager::getFsPath() const
{
    return baseDir + "/" + fsDir;
}
