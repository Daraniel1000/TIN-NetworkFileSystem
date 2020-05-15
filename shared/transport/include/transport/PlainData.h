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
    PlainData(std::vector<std::byte> byteVector);

    void append(void* byteArray, unsigned int length);

    const std::vector<std::byte>& getData() const;

    size_t getSize() const;

    std::vector<std::byte> getNBytes(size_t n, size_t offset = 0) const;

    bool operator==(const PlainData &rhs) const;

    bool operator!=(const PlainData &rhs) const;
};


#endif //MYNFS_PLAINDATA_H
