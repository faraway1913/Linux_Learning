#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signum){
    printf("\n收到%d信号,停止程序!\n",signum);
    exit(signum);
}

int main(void)
{
    //注册SIGINT信号处理函数 收到ctrl+c信号后不执行默认的函数，而是执行新的注册函数
    if(signal(SIGINT, sigint_handler) == SIG_ERR){  //terinal中使用kill -l 查看信号列表
        perror("注册新的信号处理函数失败\n");
        return 1;
    }

    //无限循环等待信号
    while(1){
        sleep(1);
        printf("你好,在吗?\n");
    }

    return 0;
}


/*
 signal 系统调用注册信号处理函数
#include <signal.h>
sighandler_t signal(int signum, sighandler_t handler);
// 信号处理函数声明
    typedef void (*sighandler_t)(int);
    signal 系统调用会注册某一信号对应的处理函数。如果注册成功，当进程收到这一信号时，将不会调用默认的处理函数，而是调用这里的自定义函数
    int signum: 要处理的信号
    sighandler_t handler: 当收到对应的 signum 信号时，要调用的函数
    return: sighandler_t 返回之前的信号处理函数，如果错误会返回 SEG_ERR
*/
