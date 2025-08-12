#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int num = 0;

int main(int argc, char const *argv[])
{
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }else if(pid == 0){
        //子进程
        num = 1;
        printf("子进程num的值是：%d\n",num);
    }else{
        //父进程
        sleep(1);
        printf("父进程num的值是：%d\n",num);
    }
    
    return 0;
}


/*学习心得
输出结果：子进程num的值是：1
        父进程num的值是：0
结果显示：子进程的num值已经修改，但父进程的num值并未变动。也就是说，子进程在其程序内修改的内容，父进程是不知道的，这就是进程间通讯存在的意义。父子进程代表了不同的资源（内存空间）。

小结：进程通信的作用是给不同进程传递信息，以此达到保持信息一致的作用。如例子中num是定义的全局变量，子进程修改了num，但父进程的num不会随之改变。
*/