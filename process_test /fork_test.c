#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    // 调用fork之前 代码都在父进程中运行
    printf("C哥教老学员%d白首勿悔\n",getpid());

    // 使用fork创建子进程
    /**
     * 不需要传参
     * return：int 进程号
     *      （1）：-1 出错
     *      （2）：父进程表示子进程的PID
     *      （3）：子进程中显示为0
     * __pid_t fork(void);
     */
    pid_t pid = fork();
    printf("\n");

    printf("%d\n",pid);

    return 0;
}