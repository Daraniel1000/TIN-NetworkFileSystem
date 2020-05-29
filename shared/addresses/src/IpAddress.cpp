#include <netinet/in.h>
#include <arpa/inet.h>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <netdb.h>
#include <stdexcept>
#include "addresses/IpAddress.h"
#include "addresses/address_error.h"

IpAddress::IpAddress(uint32_t address) : address(address) {}

IpAddress::IpAddress(char const *addressString)
{
    uint32_t nAddress;
    struct in_addr inAddr;
    int e;

    struct addrinfo hint, *res = NULL;
    int ret;

    memset(&hint, '\0', sizeof hint);

    hint.ai_family = PF_UNSPEC;
    hint.ai_flags = AI_NUMERICHOST;
    ret = getaddrinfo(addressString, NULL, &hint, &res);
    if (ret || res == NULL) { //invalid address or domain name
        struct hostent *h;
        int count = 0;

        h = gethostbyname(addressString);
        while(h_errno == TRY_AGAIN && count < 5){
            h = gethostbyname(addressString);
            count++;
        }
        if(h_errno == TRY_AGAIN)
            throw address_error(1, 1,"A temporary error occurred on an authoritative name server in gethostbyname");
        if(h_errno == NO_ADDRESS)
            throw address_error(1, 2,"Name is valid, but does not have IP address in gethostbyname");
        if(h_errno == NO_RECOVERY)
            throw  address_error(1, 3,"A nonrecoverable name server error occurred in gethostbyname");
        if(h == NULL)
            throw address_error(1, 4,"Null pointer exception in gethostbyname");
        memset(&nAddress, 0, sizeof(nAddress));
        memcpy(&nAddress,h->h_addr,h->h_length);
        address = ntohl(nAddress);

    }
    else {
        if (res->ai_family == AF_INET) { //IPv4 address
            e = inet_pton(AF_INET, addressString, &inAddr);
            if (e <= 0) {
                if (e == 0)
                    throw address_error(1, 5,"Invalid address in inet_pton");
                else
                    throw address_error(1, 6,"Not valid address family in inet_pton");
            }
            address = ntohl(inAddr.s_addr);
        }
    }
    freeaddrinfo(res);

}

uint32_t IpAddress::toNetworkOrder() const
{
    return htonl(this->address);
}

uint32_t IpAddress::toHostOrder() const
{
    return this->address;
}


