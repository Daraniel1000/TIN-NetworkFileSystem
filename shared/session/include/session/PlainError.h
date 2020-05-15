#ifndef MYNFS_PLAINERROR_H
#define MYNFS_PLAINERROR_H

#include <string>

class PlainError
{
    int8_t errorValue;
public:
    explicit PlainError(int8_t errorValue = 0) : errorValue(errorValue) {}
    int8_t getErrorValue() const { return this->errorValue; }

    bool operator==(const PlainError &rhs) const
    {
        return errorValue == rhs.errorValue;
    }

    bool operator!=(const PlainError &rhs) const
    {
        return !(rhs == *this);
    }
};


#endif //MYNFS_PLAINERROR_H
