#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <errno.h>
#include <string.h>

/**
 * @brief 演示 execve 系列函数的使用
 * 
 * execve 函数用于执行一个新的程序，完全替换当前进程
 * 推荐使用 execve，因为它是所有 exec 函数的基础实现
 * 
 * 函数原型:
 * int execve(const char *pathname, char *const argv[], char *const envp[]);
 * 
 * 参数说明:
 * - pathname: 需要执行程序的完整路径名
 * - argv[]:   命令行参数数组，以 NULL 结尾
 *             第一个参数通常是程序名
 * - envp[]:   环境变量数组，以 NULL 结尾，格式为 "KEY=VALUE"
 * 
 * 返回值:
 * - 成功: 不会返回，因为当前进程已被新程序替换
 * - 失败: 返回 -1，并设置 errno
 */
int main(int argc, char const *argv[])
{
    char *name = "CCWang";
    
    // 打印当前进程信息
    printf("我是%s %d，我现在在一楼\n", name, getpid());
    
    // 构造传递给新程序的参数数组
    // 注意: 数组必须以 NULL 结尾
    char *args[] = {
        "/home/ccwang/桌面/Linux_Learning/process_test/erlou",  // 程序路径
        name,                                                   // 传递的参数
        NULL                                                    // 参数数组结束标记
    };
    
    // 构造环境变量数组
    // 注意: 数组必须以 NULL 结尾
    char *envs[] = {
        "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin",
        NULL    // 环境变量数组结束标记
    };
    
    // 执行新程序
    // 成功时不会返回，失败时返回 -1
    int re = execve(args[0], args, envs);
    
    // 只有在 execve 执行失败时才会执行到这里
    if (re == -1) {
        printf("你没机会上二楼\n");
        printf("错误代码: %d\n", errno);
        printf("错误详情: %s\n", strerror(errno));
        printf("尝试执行的路径: %s\n", args[0]);
        
        // 检查文件是否存在
        if (access(args[0], F_OK) == -1) {
            printf("文件不存在\n");
        } else {
            printf("文件存在\n");
        }
        
        // 检查执行权限
        if (access(args[0], X_OK) == -1) {
            printf("文件没有执行权限\n");
        } else {
            printf("文件有执行权限\n");
        }
        
        return -1;
    }
    
    // 程序正常退出（实际上不会执行到这里）
    return 0;
}