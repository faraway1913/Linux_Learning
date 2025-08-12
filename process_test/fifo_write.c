#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include<fcntl.h>
#include <errno.h>


int main(int argc, char const *argv[])
{
    int fd;
    char *pipe_path = "/tmp/myfifo";
    int result = mkfifo(pipe_path, 0664);
    if(result != 0){
        if(errno != EEXIST){
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }

    //对有名管道的特殊文件 创建fd
    fd = open(pipe_path,O_WRONLY);
    if(fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buf[100];
    ssize_t read_num;
    //读取控制台数据写入到管道中
    while((read_num = read(STDIN_FILENO,buf,100)) > 0){
        write(fd,buf,read_num);
    }

    if(read_num < 0){
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("发送数据到管道完成 进程终止\n");
    close(fd);

    //释放管道
    //清除对应的文件
    if(unlink(pipe_path) == -1){
        perror("unlink");
    }

    return 0;
}


/*学习心得
mkfifo后如果报错文件已存在，报错号17（EEXIST）file exist，可以手动添加判断忽略此报错，如：
    if(result != 0){
        if(errno != EEXIST){
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }
有名管道使用后需要使用unlink释放掉有名管道，虽然有名管道创建后可以重复使用，但不推荐，容易出现管道重复报错
有名管道写入权限只能是WRONLY；读取权限只能是RDONLY

*/
