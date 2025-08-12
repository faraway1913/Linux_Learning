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
        printf("老学员%d邀请完%d后，还是在一楼学习\n",getpid(),pid);
        //等待新学员二楼结束 手动输入一个字母结束等待
        char bye = fgetc(stdin);
    }

    return 0;
}


/*学习心得
fgetc等待键盘输入，挂起进程，输入一个字符后结束等待，进程结束
终端执行ps -ef一个个往上查看父进程，最终会查找到进程号1，2.这两个进程为一切之初
或者ps -ef | grep XXX 使用管道符进行过滤，减少翻阅量
！！！更加直接简单的办法：
    pstree -p 直接查看进程,自己写的代码会有比较长的路径
    pstree 显示进程数，-p 选项显示进程号
*/