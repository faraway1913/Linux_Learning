#include<stdio.h>
#include<stdlib.h>

int main(){
    //使用标准库函数创建子进程
    /**
     * const char *__command：使用Linux命令直接创建一个子进程
     * 根据传入的命令启动一个进程
     * 参数：传入可执行的shell命令
     * return：成功返回0 不支持shell返回-1 失败返回非0
     */

    int sysR = system("ping -c 10 www.atguigu.com");
    if(sysR != 0){
        perror("system");
        exit(EXIT_FAILURE);
    }

    return 0;
}