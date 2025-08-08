#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
    char *name = "老学员";
    printf("%s%d在一楼精进\n",name, getpid());
    __pid_t pid = fork();
    if(pid == -1){
        printf("邀请新学员失败\n");
    }else if(pid == 0){
        //新学员在这里
        char *newName = "二狗";
        char *args[] = {
            "/home/ccwang/桌面/Linux_Learning/process_test/erlou",
            newName,
            NULL};
        char *envs[] = {
            "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin",
            NULL};
        int re = execve(args[0],args,envs);
        if(re == -1){
            printf("新学员上二楼失败\n");
            return 1;
        }
    }else{
        //老学员在这里
        sleep(1);
        printf("老学员%d邀请完%d后，还是在一楼学习\n",getpid(),pid);
    }

    return 0;
}

/*
学习心得：
进程的运行通常需要先fork()一下，复制父进程获得子进程，再将子进程用execve()替换成新的进程，这样，新进程就运行了，而父进程就变成了僵尸进程。
*/