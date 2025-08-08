#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
    if(argc < 2){
        printf("参数不够，上不了二楼\n");
        return 1;   //当没有参数时，应返回非零值表示错误
    }

    printf("我是%s编号%d,父进程%d, 我跟海哥上二楼啦\n",argv[1],getpid(),getppid());

    return 0;
}
