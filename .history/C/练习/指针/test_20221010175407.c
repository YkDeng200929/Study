#include <stdio.h>
#include <stdlib.h>
int main()
{
    int a[5][4] = 
    {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,16},
        {17,18,19,20}
    };
    strncmp()

    printf("%d %d %d %d %d\n", a[2], a+32, a, &a[0][0]+8, &a[0][0]-32);
    //a[2]是一个地址，{9,10,11,12}这个数组的地址

    return 0;
}