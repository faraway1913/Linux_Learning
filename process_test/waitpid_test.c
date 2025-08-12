#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char const *argv[])
{
    //fork之前
    int subprocess_status;
    printf("老学员在校区\n");
    pid_t pid = fork();
    if(pid < 0){
        perror("fork error");
    }else if(pid == 0){
        //新学员
        char *args[] = {"/usr/bin/ping",
                        "-c",
                        "10",
                        "www.atguigu.com",
                        NULL};
        char *envs[] = {NULL};
        printf("新学员%d联系海哥10次\n",getpid());
        int exR = execve(args[0],args,envs);
        if(exR < 0){
            perror("execve error");
            return -1;
        }
    }else{
        //老学员
        printf("老学员%d等待新学员%d联系\n",getpid(),pid);
        waitpid(pid,&subprocess_status,0);
    }
    printf("老学员联系新学员完成\n");

    return 0;
}


/*学习心得
主要理解waitpid()和用法
pid_t waitpid waitpid (pid_t pid, int *status, int options);
return：返回值取决于其执行结果
        成功时: 返回状态已改变的子进程的进程 ID。
        使用 WNOHANG 且没有子进程退出时: 返回 0。
        出错时: 返回 -1，并设置 errno 以指示错误原因。
parameters:
pid_t pid：指定了要等待的子进程，有以下几个参数值：
                > 0: 等待进程 ID 等于 pid 的特定子进程
                -1: 等待任何一个子进程。在这种情况下，waitpid() 的行为与 wait() 函数类似
                0: 等待进程组 ID 与调用进程的进程组 ID 相同的任何子进程
                < -1: 等待进程组 ID 等于 pid 绝对值的任何子进程
int *status：指向整型变量的指针，用于存储子进程的状态信息。
            如果你子进程的退出状态不感兴趣，可以将其设置为 NULL。
            如果提供了 status 指针，waitpid() 会将子进程的返回状态存放在 *status 中。
options: 这个参数允许你修改 waitpid() 的行为。可以是 0，或者以下一个或多个常量的按位或组合：
        0：阻塞等待：父进程会一直阻塞，直到指定的子进程状态发生变化（通常是子进程终止）
        WNOHANG: 如果指定的子进程还没有改变状态，waitpid() 不会阻塞，而是立即返回 0。这对于检查子进程状态而不挂起父进程非常有用
        WUNTRACED: 除了已终止的子进程外，也返回已停止（但未被跟踪）的子进程的状态信息
        WCONTINUED: 报告已停止后又被 SIGCONT 信号恢复的子进程的状态

wait(&status) 等价于 waitpid(-1, &status, 0)
所以waitpid是最常用的，wait可以不掌握。

什么时候使用waitpid？：
1.管理多个子进程: 当一个父进程创建了多个子进程时，waitpid() 允许父进程有选择地等待特定的子进程。
2.避免僵尸进程: 当一个子进程终止时，它的进程描述符仍然保留在内存中，直到父进程通过 wait() 或 waitpid() 获取其状态信息。这些已终止但未被父进程回收的子进程被称为“僵尸进程”。定期调用 waitpid() 可以有效地清理这些僵尸进程，释放系统资源。
3.非阻塞轮询: 使用 WNOHANG 选项，父进程可以在其主循环中定期检查子进程的状态，而不会被阻塞，从而可以同时处理其他任务
*/
