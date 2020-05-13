#ifndef MYNFS_PLAINDATA_H
#define MYNFS_PLAINDATA_H


#include <vector>

class PlainData
{
/**
 * TODO:
 * some vector of bytes inside
 * operations of adding, MAYBE deleting
 * getting const reference to vector
 */

    std::vector<std::byte> byteVector;

public:
    PlainData() = default;
    PlainData(void* byteArray, unsigned int length);

    void append(void* byteArray, unsigned int length);

    const std::vector<std::byte>& getData() const;
};


#endif //MYNFS_PLAINDATA_H
