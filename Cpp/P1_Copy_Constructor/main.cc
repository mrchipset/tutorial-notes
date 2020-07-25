#include "Foo.h"

int main()
{
    Foo bar1(10);
    Foo bar2 = bar1;
    bar1.printMe();
    bar2.printMe();
    return 0;
}