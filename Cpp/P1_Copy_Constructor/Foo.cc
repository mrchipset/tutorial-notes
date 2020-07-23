#include "Foo.h"


Foo::Foo(int intVal, int * intPtr, std::string name) 
    : m_intVal(intVal), m_intPtr(intPtr), m_name(name)
{

}

Foo::Foo(const Foo& other)
{
    m_intVal = other.m_intVal;
    m_intPtr = other.m_intPtr;
    m_name = other.m_name;
}

void Foo::printMe()
{
    std::cout << "m_intVal:\t" << m_intVal
    << "m_intPtr:\t" << m_intPtr << "\t *m_intPtr:\t" << m_intPtr[5]
    << "\tm_name:\t" << m_name << std::endl; 
}