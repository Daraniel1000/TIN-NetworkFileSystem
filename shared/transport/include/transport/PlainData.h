#ifndef MYNFS_PLAINDATA_H
#define MYNFS_PLAINDATA_H


#include <vector>
#include <cstddef>

class PlainData
{
    std::vector<std::byte> byteVector;

public:
    PlainData() = default;
    PlainData(void* byteArray, unsigned int length);

    void append(void* byteArray, unsigned int length);

    const std::vector<std::byte>& getData() const;
};


#endif //MYNFS_PLAINDATA_H
