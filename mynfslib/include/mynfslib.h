#ifndef MYNFS_MYNFSLIB_H
#define MYNFS_MYNFSLIB_H

#include <cstdint>

int16_t mynfs_open(char const *host, char const *path, uint8_t oflag);
int16_t mynfs_read(char const *host, int16_t fd, void *buf, int16_t count);

#endif //MYNFS_MYNFSLIB_H
