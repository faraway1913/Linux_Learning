#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    pid_t cpid;
    int pipefd[2];

    //程序功能：将程序传递进来的第一个命令行参数 通过管道传递给子进程
    if (argc != 2){
        fprintf(stderr,"%s，请填写要传递的信息\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    //创建管道
    if(pipe(pipefd) == -1){
        perror("创建管道失败");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if(cpid == -1){
        perror("邀请新学员失败!\n");
        exit(EXIT_FAILURE);
    }
    
    if(cpid == 0){
        //子进程 读取管道的数据
        close(pipefd[1]);
        char *str = "新学员接收信息\n";
        char buf;
        write(STDOUT_FILENO,str,strlen(str));
        while (read(pipefd[0],&buf,1) > 0)
        {
            write(STDOUT_FILENO,&buf,1);
        }
        write(STDOUT_FILENO,"\n",1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);
    }else{
        //父进程 给管道写入数据
        close(pipefd[0]);
        //将数据写入管道中 提供给子进程读
        printf("父进程%d给子进程传递信息\n",getpid());
        write(pipefd[1],argv[1],strlen(argv[1]));
        close(pipefd[1]);
        waitpid(cpid,NULL,0);
        exit(EXIT_SUCCESS);
    }

    return 0;
}


/*学习心得
匿名管道使用：只能在有父子关系的进程间使用，使用场景受限
程序功能：使用管道，让父进程写入数据提供给子进程读取
写入的数据是需要传入的参数，因此在Makefile时需要添加传入的内容，即 -./$@ "test"
使用写管道端的进程，初始需要关闭读端，写入后要记得关闭写端；同理，使用读管道的进程，初始需要关闭写端，读取后记得关闭读端
进程A和进程B，都拥有读写两个端，但是在进行通讯时，A读B写或者B写A读，分别只能开启一个端，若要实现双端通信，需要多创建一个管道
*/