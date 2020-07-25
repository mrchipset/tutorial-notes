#include "Foo.h"
#include <iostream>


Foo::Foo(int val)
{
#ifdef STACK_MEMBER
    m_member = val;
#else
    m_member = new int;
    *m_member = val;
#endif
}

#ifndef STACK_MEMBER
Foo::Foo(const Foo& other)
{
    m_member = new int;
    *m_member = *other.m_member;
}

Foo::~Foo()
{
    delete m_member;
    m_member=nullptr;
}
#endif

void Foo::printMe()
{
#ifdef STACK_MEMBER
    std::cout << "m_member:" << m_member 
        << "&m_member:" << &m_member << std::endl;
#else
    std::cout << "m_member:" << *m_member 
        << "&m_member:" << m_member << std::endl;
#endif
}

