#include <stdio.h>
typedef int (*Func_point)();

int sum(int x, int y)
{
    return x+y;
}

int main()
{
    Func_point fptr = sum;
    fptr();

    return 0;
}