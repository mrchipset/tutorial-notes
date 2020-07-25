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
// #define STACK_MEMBER
class Foo
{
public:
    Foo(int val);
#ifndef STACK_MEMBER
    Foo(const Foo& other);
    ~Foo();
#endif
    void printMe();
private:
#ifdef STACK_MEMBER
    int m_member;
#else
    int* m_member;
#endif
};