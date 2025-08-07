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
        int re = execve(argv[0],args,envs);
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


/**学习心得
 * Makefile:
 * fork_execve_test: fork_execve_test.c erlou
	    -$(CC) -o $@ $(firstword $^)
	    -./$@
	    -rm ./$@ ./$(lastword $^)
 * 1.运行结果：
    ccwang@ccwang-virtual-machine:~/桌面/Linux_Learning/process_test$ cd "/home/ccwang/桌面/Linux_Learning/process_test" && make -f Makefile fork_execve_test
    gcc -o fork_execve_test fork_execve_test.c
    ./fork_execve_test
    老学员5751在一楼精进
    老学员5751邀请完5752后，还是在一楼学习
    老学员5752在一楼精进
    老学员5752邀请完5753后，还是在一楼学习
    rm ./fork_execve_test ./erlou
    我是二狗 5753, 我跟海哥上二楼啦
 * 2.真正的执行过程：
 *  进程 5751：原始进程执行，创建子进程 5752
 *   进程 5752：子进程执行，但调用 execve() ，因为execve()中argv[0]代表当前./fork_execve_test,产生递归，重新执行了当前程序
 *   进程 5752（重新执行）：作为新实例运行，重新打印老学员5752在一楼精进 老学员5752邀请完5753后，还是在一楼学习。fork()创建子进程 5753。这一次，它的 argv 不再是 ./fork_execve_test，而是 5752调用execve()时传入的 args，即 {"/home/.../erlou", "二狗", NULL}。所以，此时进程5752的 argv[0] 是 "/home/ccwang/桌面/Linux_Learning/process_test/erlou"
 *   进程 5753：最内层子进程执行，同样调用 execve() ，执行/home/.../erlou，打印我是二狗 5753, 我跟海哥上二楼啦
 */