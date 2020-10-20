#include "Socket.h"

Socket::Socket(std::string const& ip, int port) :
    mIp(ip), mPort(port)
{
    mIsOpen = Open(mIp, mPort);
}

Socket::~Socket()
{
    if (isOpen())
    {
        Close();
    }
}

bool Socket::Open(std::string const& ip, int port)
{
    if (isOpen())
    {
        Close();
    }

    if (ip.empty() || port <= 0)
    {
        return false;
    }

    mFd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&mSockAddr, 0x00, sizeof(mSockAddr));
    mSockAddr.sin_family = AF_INET;
    mSockAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &mSockAddr.sin_addr);
    if (connect(mFd, reinterpret_cast<const sockaddr*>(&mSockAddr),
         sizeof(mSockAddr)) < 0)
    {
        return false;
    }
    return true;
}

void Socket::Close()
{
    if (isOpen())
    {
        close(mFd);
        mIsOpen = false;
    }
}

bool Socket::isOpen()
{
    return mIsOpen;
}

int Socket::Read(char* pBuff, int nLen)
{
    return recv(mFd, pBuff, nLen, 0);
}

int Socket::Write(char* pBuff, int nLen)
{
    return send(mFd, pBuff, nLen, 0);
}