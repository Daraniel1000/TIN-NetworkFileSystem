#ifndef MYNFS_MYNFSLIB_H
#define MYNFS_MYNFSLIB_H

#include <cstdint>

int16_t mynfs_open(char const *host, char const *path, uint8_t oflag);
int16_t mynfs_read(char const *host, int16_t fd, void *buf, int16_t count);
int16_t mynfs_write(char *host, int16_t fd, void *buf, int16_t count);
int32_t mynfs_lseek(char *host, int16_t fd, int32_t offset, uint8_t whence);
int8_t mynfs_close(char *host, int16_t fd);
int8_t mynfs_unlink(char *host, char *path);

extern int mynfs_error;
extern std::string mynfs_error_message;

#endif //MYNFS_MYNFSLIB_H
