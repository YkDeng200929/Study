#include <stdio.h>

void printarr(int *arr)
{
    for(int i=0; i <= (int)sizeof(arr)/sizeof(int); i++)
    {
        printf("%d ", *(arr+i));
    }
    printf("\n");
}

int main(void)
{
    int a[3] = {1,2,3};

    printf("%d %d %d\n", *a, *a+1, *a+2);
    printf("%p %p %p\n", a, a+1, a+2);
    printf("%d %d %d\n", (*a)+1, (*a+1)+1, (*a+2)+1);
    printa

    return 0;
}