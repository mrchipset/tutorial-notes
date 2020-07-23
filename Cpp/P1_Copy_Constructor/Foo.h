/**
 * @file Foo.h
 * @author X.F.Zhou (xfzhou233@gmail.com)
 * @brief Demo for Copy Constructor
 * @version 0.1
 * @date 2020-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <iostream>
#include <string>

class Foo
{
public:
    Foo(int intVal, int* intPtr, std::string name);
    Foo(const Foo& other);

    void printMe();
private:
    int m_intVal;
    int* m_intPtr;
    std::string m_name;
};