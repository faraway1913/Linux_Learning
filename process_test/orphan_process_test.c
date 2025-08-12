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
            "/home/ccwang/桌面/Linux_Learning/process_test/erlou_block",
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
        printf("老学员%d邀请完%d后，还是在一楼学习\n",getpid(),pid);
    }

    return 0;
}


/*学习心得
孤儿进程
父进程结束后，子进程仍在运行，子进程就变成了孤儿进程，此时这个孤儿进程会被其祖先自动领养
这时子进程因为和终端切断了联系，所以很难再进行标准输入使其停止了
因此，写代码时一定注意避免孤儿进程的产生！！！切记！！！

*/