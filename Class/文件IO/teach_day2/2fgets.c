#include <stdio.h>

int main()
{
	char buf[8] = {0};

	fgets(buf, sizeof(buf), stdin);//按行输入，遇到'\n'停止，最多读取size-1个字符

	printf("buf: %s",buf);
	return 0;
}
