#ifndef MY_SOCKET_H
#define MY_SOCKET_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>

#include <arpa/inet.h>
#include <netinet/in.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>

class Socket
{
public:
    Socket(std::string const& ip, int port);
    ~Socket();
    bool Open(std::string const& ip=std::string(), int port=-1);
    void Close();
    bool isOpen();
    int Read(char* pBuff, int nLen);
    int Write(char* pBuff, int nLen);
private:
    std::string mIp;
    int mPort;
    bool mIsOpen;
    int mFd;
    struct sockaddr_in mSockAddr;
};
#endif