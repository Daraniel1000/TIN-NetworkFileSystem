#include <catch.hpp>
#include <fcntl.h>

#include "mynfslib.h"

TEST_CASE("mynfs_open working correctly", "[mynfs]")
{
    mynfs_open("127.0.0.1", "/dir/file", O_RDONLY);
}