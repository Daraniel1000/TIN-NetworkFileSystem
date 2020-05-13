#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <fff.h>

DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC(int, close, int);

int close_custom_fake(int fd)
{
    //sample mock
    return 0;
}

TEST_CASE("Description", "[TAG]")
{
    close_fake.custom_fake = close_custom_fake; // mock entire function (before calling)
    close_fake.return_val = 1; // set return value (before calling)

    auto fd = close_fake.arg0_val; // capture passed argument value (after calling)

    CHECK(true == true);
}