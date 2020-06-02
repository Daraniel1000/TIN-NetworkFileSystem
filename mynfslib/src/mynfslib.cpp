#include <application/mynfs/replies/OpenReply.h>
#include <application/mynfs/requests/OpenRequest.h>
#include <application/mynfs/replies/ReadReply.h>
#include <application/mynfs/requests/ReadRequest.h>
#include <application/mynfs/replies/WriteReply.h>
#include <application/mynfs/requests/WriteRequest.h>
#include <application/mynfs/replies/LseekReply.h>
#include <application/mynfs/requests/LseekRequest.h>
#include <application/mynfs/replies/CloseReply.h>
#include <application/mynfs/requests/CloseRequest.h>
#include <application/mynfs/replies/UnlinkReply.h>
#include <application/mynfs/requests/UnlinkRequest.h>
#include <mynfslib.h>
#include <transport/socket_error.h>
#include <addresses/address_error.h>
#include <cstring>
#include <sstream>
#include <application/mynfs/bad_argument_error.h>

#include "endpoint/ClientEndpoint.h"
#include "authentication_error.h"

int mynfs_error = 0;
std::string mynfs_error_message;

int16_t mynfs_open(char const *host, char const *path, uint8_t oflag)
{
    try
    {
        // create endpoint
        ClientEndpoint clientEndpoint;

        // send request and get reply
        OpenReply readReply = clientEndpoint.send<OpenRequest, OpenReply>
                (
                        NetworkAddress(host),
                        OpenRequest(path, oflag)
                );
        // react to error here
        if(readReply.getError().getErrorValue() > 0)
        {
            mynfs_error = 4000 + readReply.getError().getErrorValue();
            mynfs_error_message = "Reply error. " + readReply.getError().toString();
            return -1;
        }

        // return reply data
        return readReply.getDescriptor();
    }
    catch (address_error& e)
    {
        mynfs_error = 1000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Address error. " + std::string(e.what());
    }
    catch (bad_argument_error& e)
    {
        mynfs_error = 2000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Bad argument error. " + std::string(e.what());
    }
    catch (socket_error& e)
    {
        mynfs_error = 3000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Network error. " + std::string(e.what());
    }
    catch (authentication_error& e)
    {
        mynfs_error = 5000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Authentication error. " + std::string(e.what());
    }
    catch (std::exception& e)
    {
        mynfs_error = 6000;
        mynfs_error_message = "Unknown error. " + std::string(e.what());
    }

    return -1;
}

int16_t mynfs_read(char const *host, int16_t fd, void *buf, int16_t count)
{
    try {
        // create endpoint
        ClientEndpoint clientEndpoint;

        // send request and get reply
        ReadReply readReply = clientEndpoint.send<ReadRequest, ReadReply>
                (
                        NetworkAddress(host),
                        ReadRequest(fd, count)
                );

        // react to error here
        if(readReply.getError().getErrorValue() > 0)
        {
            mynfs_error = 4000 + readReply.getError().getErrorValue();
            mynfs_error_message = "Reply error. " + readReply.getError().toString();
            return -1;
        }

        memcpy(buf, readReply.getData().getData().data(), readReply.getData().getSize());

        //return
        return static_cast<int16_t>(readReply.getData().getSize());
    }
    catch (address_error& e)
    {
        mynfs_error = 1000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Address error. " + std::string(e.what());
    }
    catch (bad_argument_error& e)
    {
        mynfs_error = 2000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Bad argument error. " + std::string(e.what());
    }
    catch (socket_error& e)
    {
        mynfs_error = 3000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Network error. " + std::string(e.what());
    }
    catch (authentication_error& e)
    {
        mynfs_error = 5000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Authentication error. " + std::string(e.what());
    }
    catch (std::exception& e)
    {
        mynfs_error = 6000;
        mynfs_error_message = "Unknown error. " + std::string(e.what());
    }

    return -1;
}

int16_t mynfs_write(char const *host, int16_t fd, void *buf, int16_t count)
{
    try {
        // create endpoint
        ClientEndpoint clientEndpoint;

        // send request and get reply
        WriteReply readReply = clientEndpoint.send<WriteRequest, WriteReply>
                (
                        NetworkAddress(host),
                        WriteRequest(fd, buf, count)
                );

        // react to error here
        if(readReply.getError().getErrorValue() > 0)
        {
            mynfs_error = 4000 + readReply.getError().getErrorValue();
            mynfs_error_message = "Reply error. " + readReply.getError().toString();
            return -1;
        }

        return readReply.getCount();
    }
    catch (address_error& e)
    {
        mynfs_error = 1000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Address error. " + std::string(e.what());
    }
    catch (bad_argument_error& e)
    {
        mynfs_error = 2000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Bad argument error. " + std::string(e.what());
    }
    catch (socket_error& e)
    {
        mynfs_error = 3000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Network error. " + std::string(e.what());
    }
    catch (authentication_error& e)
    {
        mynfs_error = 5000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Authentication error. " + std::string(e.what());
    }
    catch (std::exception& e)
    {
        mynfs_error = 6000;
        mynfs_error_message = "Unknown error. " + std::string(e.what());
    }
    return -1;
}

int32_t mynfs_lseek(char const *host, int16_t fd, int32_t offset, uint8_t whence)
{
    try {
        // create endpoint
        ClientEndpoint clientEndpoint;

        // send request and get reply
        LseekReply readReply = clientEndpoint.send<LseekRequest, LseekReply>
                (
                        NetworkAddress(host),
                        LseekRequest(fd, offset, whence)
                );

        // react to error here
        if(readReply.getError().getErrorValue() > 0)
        {
            mynfs_error = 4000 + readReply.getError().getErrorValue();
            mynfs_error_message = "Reply error. " + readReply.getError().toString();
            return -1;
        }

        //return offset
        return readReply.getOffset();
    }
    catch (address_error& e)
    {
        mynfs_error = 1000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Address error. " + std::string(e.what());
    }
    catch (bad_argument_error& e)
    {
        mynfs_error = 2000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Bad argument error. " + std::string(e.what());
    }
    catch (socket_error& e)
    {
        mynfs_error = 3000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Network error. " + std::string(e.what());
    }
    catch (authentication_error& e)
    {
        mynfs_error = 5000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Authentication error. " + std::string(e.what());
    }
    catch (std::exception& e)
    {
        mynfs_error = 6000;
        mynfs_error_message = "Unknown error. " + std::string(e.what());
    }

    return -1;
}

int8_t mynfs_close(char const *host, int16_t fd)
{
    try {
        // create endpoint
        ClientEndpoint clientEndpoint;

        // send request and get reply
        CloseReply readReply = clientEndpoint.send<CloseRequest, CloseReply>
                (
                        NetworkAddress(host),
                        CloseRequest(fd)
                );

        // react to error here
        if(readReply.getError().getErrorValue() > 0)
        {
            mynfs_error = 4000 + readReply.getError().getErrorValue();
            mynfs_error_message = "Reply error. " + readReply.getError().toString();
            return -1;
        }

        return 0;
    }
    catch (address_error& e)
    {
        mynfs_error = 1000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Address error. " + std::string(e.what());
    }
    catch (bad_argument_error& e)
    {
        mynfs_error = 2000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Bad argument error. " + std::string(e.what());
    }
    catch (socket_error& e)
    {
        mynfs_error = 3000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Network error. " + std::string(e.what());
    }
    catch (authentication_error& e)
    {
        mynfs_error = 5000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Authentication error. " + std::string(e.what());
    }
    catch (std::exception& e)
    {
        mynfs_error = 6000;
        mynfs_error_message = "Unknown error. " + std::string(e.what());
    }

    return -1;
}

int8_t mynfs_unlink(char const *host, char const *path)
{
    try {
        // create endpoint
        ClientEndpoint clientEndpoint;

        // send request and get reply
        UnlinkReply readReply = clientEndpoint.send<UnlinkRequest, UnlinkReply>
                (
                        NetworkAddress(host),
                        UnlinkRequest(path)
                );

        // react to error here
        if(readReply.getError().getErrorValue() > 0)
        {
            mynfs_error = 4000 + readReply.getError().getErrorValue();
            mynfs_error_message = "Reply error. " + readReply.getError().toString();
            return -1;
        }

        return 0;
    }
    catch (address_error& e)
    {
        mynfs_error = 1000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Address error. " + std::string(e.what());
    }
    catch (bad_argument_error& e)
    {
        mynfs_error = 2000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Bad argument error. " + std::string(e.what());
    }
    catch (socket_error& e)
    {
        mynfs_error = 3000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Network error. " + std::string(e.what());
    }
    catch (authentication_error& e)
    {
        mynfs_error = 5000 + 100*e.getMajorCode() + e.getMinorCode();
        mynfs_error_message = "Authentication error. " + std::string(e.what());
    }
    catch (std::exception& e)
    {
        mynfs_error = 6000;
        mynfs_error_message = "Unknown error. " + std::string(e.what());
    }

    return -1;
}
