#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
    /**
     * exec系列函数 父进程跳转进入一个新的进程
     * 推荐使用execve
     * int execve(const char *__path, char *const __argv[], char *const __envp[]);
     * Parameters:
     * char *__path：需要执行程序的完整路径名
     * char *const __argv[]：指向字符串数组的指针 需要传入多个参数
     *      （1）需要执行的程序命令（同*__path）
     *      （2）执行程序需要传入的参数
     *      （3）最后一个参数必须是NULL
     * char *const __envp[]：指向字符串数组的指针 需要传入多个环境变量参数
     *      （1）环境变量参数 固定格式key=value
     *      （2）最后一个参数必须是NULL
     * return：成功就回不来了 下面的代码就没有意义
     *         失败返回-1
     * 
     */

    char *name = "CCWang";
    printf("我是%s %d，我现在在一楼\n",name,getpid());
    // 参数没写够也能跳转，错误信息会在新程序中
    // char *argv[] = {"/home/ccwang/桌面/Linux_Learning/process_test/erlou",NULL}
    char *args[] = {"/home/ccwang/桌面/Linux_Learning/process_test/erlou",name, NULL};
    //环境变量可以不传
    // char *envp[] = {NULL};
    char *envs[] = {"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin",NULL};

    int re = execve(args[0],args,envs);
    if(re == -1){
        printf("你没机会上二楼\n");
        return -1;
    }

    return 0;
}
