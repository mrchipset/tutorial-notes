#include <iostream>
#include <windows.h>

int main()
{
    std::cout << "Current Process Id (child process): " <<  GetCurrentProcessId() << std::endl;
    std::cout << "Test program process!" << std::endl;
    while (true) {
        Sleep(1000);
    }
    return 0;
}