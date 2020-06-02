#include <application/mynfs/errors/OpenReplyError.h>
#include <application/mynfs/replies/OpenReply.h>
#include <application/mynfs/requests/OpenRequest.h>
#include <fcntl.h>
#include <algorithm>
#include <utility>
#include "OpenHandler.h"

OpenHandler::OpenHandler(DomainData requestData, NetworkAddress requestAddress, DomainData &replyData,
                         PlainError &replyError,
                         AccessManager &accessManager) : Handler(std::move(requestData),
                                                                 requestAddress,
                                                                 replyData,
                                                                 replyError,
                                                                 accessManager)
{
    int errorList[] = {EACCES, EEXIST, ELOOP, ENAMETOOLONG, ENFILE, ENOENT, ENOSPC, ENOTDIR, EINVAL};
    possibleErrors.assign(errorList, errorList + sizeof(errorList) / sizeof(int));
}

int getAccessMode(uint16_t oflag)
{
    return oflag & O_ACCMODE;
}

bool isAccessModePermitted(const AccessManager& accessManager, const IpAddress& address, uint16_t oflag)
{
    auto accessMode = getAccessMode(oflag);

    switch (accessMode)
    {
        case O_RDONLY:
            return accessManager.hasReadRight(address);
        case O_WRONLY:
            return accessManager.hasWriteRight(address);
        case O_RDWR:
            return accessManager.hasReadWriteRight(address);
        default:
            return false;
    }
}

void OpenHandler::handle()
{
    int fd;
    int error = 0;
    // create request
    OpenRequest request(this->requestData);

    if (!this->accessManager.isPathPermitted(request.getPath()))
    {
        fd = -1;
        error = EACCES;
    }
    else if(!isAccessModePermitted(this->accessManager, this->requestAddress.getAddress(), request.getOflag()))
    {
        fd = -1;
        error = EACCES;
    }
    else
    {
        // get request data
        auto pathStr = (this->accessManager.getFsPath() + "/" + request.getPath());
        const char *path = pathStr.data();
        auto oflag = request.getOflag();

        // do something with it here
        fd = open(path, oflag, 0777);

        if (fd == -1)
        {
            error = errno;
            if (std::find(possibleErrors.begin(), possibleErrors.end(), error) == possibleErrors.end())
                error = -1;
        }
        else
            fd = this->accessManager.generateAppDescriptor(this->requestAddress.getAddress(), fd);
    }
    OpenReply reply(fd, OpenReplyError(error));

    // save reply and error
    this->replyData = reply.serialize();
    this->replyError = reply.getError().serialize();

}

OpenHandler::~OpenHandler()
{

}

