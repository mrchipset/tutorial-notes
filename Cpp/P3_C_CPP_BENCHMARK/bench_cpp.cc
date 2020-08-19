#include <iostream>
#include <cstring>

int main()
{
    int i = 0;
    int j = 0;
    int k = 0;

    const int len = 1024 * 512;
    char buff[1024 * 512];
    char buff2[1024 * 512];
    for (i = 0; i < 1000; i++)
    {
        for (k = 0; k < 1000; k++)
        {
            memset(buff, 0x00, sizeof(char) * len);
            memset(buff2, 0xff, sizeof(char) * len);
            memcpy(buff, buff2, sizeof(char) * len);
            memcpy(buff2, buff, sizeof(char) * len);
        }
        // std::cout << "Loop num: " << i << std::endl;
    }

    return 0;
}