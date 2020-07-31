// P2_AVX_Demo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <intrin.h>
#include <ctime>

float sumfloat_base(const float* pBuff, size_t nBuff)
{
    float s = 0;
    for (size_t i = 0; i < nBuff; ++i)
    {
        s += pBuff[i];
    }
    return s;
}

// 双精度浮点数组求和_AVX版.
double sumfloat_avx(const float* pbuf, size_t cntbuf)
{
    float s = 0;    // 求和变量.
    size_t i;
    size_t nBlockWidth = 8;    // 块宽. AVX寄存器能一次处理8个float.
    size_t cntBlock = cntbuf / nBlockWidth;    // 块数.
    size_t cntRem = cntbuf % nBlockWidth;    // 剩余数量.
    __m256 yfdSum = _mm256_setzero_ps();    // 求和变量。[AVX] 
    __m256 yfdLoad;    // 加载.
    const float* p = pbuf;    // AVX批量处理时所用的指针.
    const float* q;    // 将AVX变量上的多个数值合并时所用指针.

   
    // AVX批量处理.
    for (i = 0; i < cntBlock; ++i)
    {
        yfdLoad = _mm256_load_ps(p);    // [AVX] 
        yfdSum = _mm256_add_ps(yfdSum, yfdLoad);    // [AVX] 
        p += nBlockWidth;
    }
    // 合并.
    q = (const float*)&yfdSum;
    s = q[0] + q[1] + q[2] + q[3] + q[4] + q[5] + q[6] + q[7];

    // 处理剩下的.
    for (i = 0; i < cntRem; ++i)
    {
        s += p[i];
    }

    return s;
}

int main()
{
    const size_t nArray = 100000;
    const size_t nLoop = 100000;
    float* fArray = new float[nArray];
    time_t s, e;
    s = clock();
    for (int i=0;i<nLoop;++i)
        float x = sumfloat_base(fArray, nArray);
    e = clock();
    std::cout << "Base loop used:" << (double)(e - s) / CLOCKS_PER_SEC << std::endl;

    s = clock();
    for (int i = 0; i < nLoop; ++i)
        float x = sumfloat_avx(fArray, nArray);
    e = clock();
    std::cout << "AVX loop used:" << (double)(e - s) / CLOCKS_PER_SEC << std::endl;
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
