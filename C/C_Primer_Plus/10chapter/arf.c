#include <stdio.h>
#define SIZE 5

// 显示数组的内容
void show_array(const double ar[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%8.3f", ar[i]);
	putchar('\n');
}

// 把数组的每个元素都乘以相同的值
void mult_array(double ar[], int n, double mult)
{
	for (int i = 0; i < n; i++)
		ar[i] *= mult;
}

int main(void)
{
	double dip[SIZE] = {20.0, 17.66, 8.2, 15.3, 22.2};

	printf("The original dip array:\n");
	show_array(dip, SIZE);
	mult_array(dip, SIZE, 2.5);

	printf("The dip array after calling mult_array():\n");
	show_array(dip, SIZE);

	return 0;
}
