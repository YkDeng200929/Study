#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	pid_t pid,pid2;
	int status;
	pid = fork();
	if(pid == -1)
	{
		perror("fork");
		return -1;
	}else if(pid == 0)
	{
		sleep(100);
		printf("child exit\n");
	}else
	{
		while (1)
		{
			pid2 = waitpid(-1, &status, WNOHANG);
			// 回收僵尸子进程资源, 此时等价于wait(status), 使用
			// 以阻塞方式调用
			if(pid2 == -1)
			{
				perror("wait");
				return -1;
			}
			else if (pid2 == 0)
			{
				continue;
			}
			else
			{
				if(WIFEXITED(status))// 判断是否因exit()或者_exit()退出, 得到exit里的值
				{
					printf("child exit() or _exit() , return value = %d\n",WEXITSTATUS(status));
				}
				if(WIFSIGNALED(status)) // 判断是否因信号退出
				{
					printf("child terminates by signal ,signal number = %d\n", WTERMSIG(status));
				}
				printf("child exit pid = %d\n",pid2);
				break;
			}
		}
	}
	while(1);
	return 0;
}
