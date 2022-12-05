#include <stdio.h>
typedef int (*temp)();
int foo(int (*)(), int a);
int loo();
temp poo();

int main()
{
    int (*fooP)(int (*)(), int);
    fooP = &foo;
    printf("%d", fooP(*(poo()), 3));
}

int foo(int func2Ptr(), int a)
{
    return func2Ptr() * a * 2;
}

int loo()
{
    return 10;
}
temp poo()
{
    return &loo;
}