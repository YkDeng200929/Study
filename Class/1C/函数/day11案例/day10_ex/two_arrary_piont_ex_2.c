#include <stdio.h>

int main(int argc, const char *argv[])
{
	int a[2][3] = {10, 20, 30, 40, 50, 60};
	int (*p)[3] = a;
	int i = 0, j = 0;

	for(i = 0; i < 2; i ++)
	{
		for(j = 0; j < 3; j++)
		{
			//printf("%d ", p[i][j]);
			printf("%d ", *(*(p + i) + j));
		}
		putchar('\n');
	}
	
	return 0;
}
