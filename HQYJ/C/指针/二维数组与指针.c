#include <stdio.h>

int main()
{
    int arr[3][3]={1,2,3,4,5,6,7,8};
    printf("%d\n", arr);
    printf("%d\n", arr[0]);// 说明arr[0]是二维数组第一个元素的地址;
    printf("%d\n", *arr[0]);// *arr[0] == arr[0][0]
    printf("%d\n", *(arr[0]+1));// *(arr[0]+1) == arr[0][1]
    int (*arr_point)[3];
    arr_point = arr;// arr_point已指向arr
    printf("%d %d %d\n", arr_point, *arr_point, **arr_point);
/*
数组指针：
    数组元素的类型 (*指针变量名) [指向数组的元素个数]

    int a[2][3]; a 可以理解为 &a[0] a[0] == int [3] &a[3] == int (*)[3]
    int (*p)[3] = &a[0] == int (*p)[3] = a
    p 又叫行指针即表示行的指针 p 的类型是int (*)[3]， p的目标类型是int [3]
----------------------------------------------------------------
    列指针*p = a[0]，则p称列指针
    a[0] <==> &a[0][0]
    int *q = a[0]; *q = &a[0][0]
----------------------------------------------------------------
    行指针和列指针的转换
    int a[][3]
    int (*p)[3];// 行指针
    int *q;//列指针
    行-->列

*/


    return 0;
}