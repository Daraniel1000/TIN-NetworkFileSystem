#ifndef MYNFS_MYNFSERROR_H
#define MYNFS_MYNFSERROR_H

#include <unordered_map>
#include "session/PlainError.h"

class MyNFSError
{
protected:
    int8_t errorValue;
public:
    explicit MyNFSError(int8_t errorValue = 0) : errorValue(errorValue) {}
    explicit MyNFSError(const PlainError& error) : MyNFSError(error.getErrorValue()) {}
    virtual ~MyNFSError() = default;

    int8_t getErrorValue() const { return this->errorValue; }
    virtual std::string toString() const = 0;
    PlainError serialize() const { return PlainError(this->errorValue); }

    bool operator==(const MyNFSError &rhs) const
    {
        return errorValue == rhs.errorValue;
    }

    bool operator!=(const MyNFSError &rhs) const
    {
        return !(rhs == *this);
    }
};


#endif //MYNFS_MYNFSERROR_H
