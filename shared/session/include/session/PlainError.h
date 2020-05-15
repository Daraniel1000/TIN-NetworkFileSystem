#ifndef MYNFS_PLAINERROR_H
#define MYNFS_PLAINERROR_H

#include <string>

class PlainError
{
    int8_t errorValue;
public:
    explicit PlainError(int8_t errorValue = 0) : errorValue(errorValue) {}
    int8_t getErrorValue() const { return this->errorValue; }
};


#endif //MYNFS_PLAINERROR_H
