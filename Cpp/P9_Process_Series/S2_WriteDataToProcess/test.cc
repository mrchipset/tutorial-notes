#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

int main()
{
    std::string s;
    std::cout << "Current Process Id (child process): " <<  GetCurrentProcessId() << std::endl;
    std::cout << "Test program process!" << std::endl;
    // std::cout.flush();
    std::getline(std::cin, s);
    std::cout << "Get from parent:\t" << s << std::endl;
    std::ofstream o;
    o.open("log.txt", std::ios_base::out);
    o << s;
    return 0;
}