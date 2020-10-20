#include <iostream>
#include "Socket.h"


int main(int, char**) {
    std::cout << "Hello, world!\n";
    Socket socket("127.0.0.1", 10001);
    std::cout << "Open Status:" << socket.isOpen() << std::endl;
    std::string send = "Hello";
    socket.Write(const_cast<char *>(send.c_str()), send.length());
    char recvBuff[1024];
    int n = socket.Read(recvBuff, 1024);
    recvBuff[n] = '\0';
    std::cout << "Recv Length:" << n << "\t" << recvBuff;
    return 0;
}
