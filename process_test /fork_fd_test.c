#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    //fork之前
    //打开一个文件
    int fd = open("io.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if(fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    printf("初始文件描述符 fd = %d\n", fd);
    
    char buffer[1024];//缓冲区存放写出的数据
    pid_t pid = fork();

    if(pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }else if(pid == 0){
        //子进程代码
        printf("子进程%d: 文件描述符 fd = %d\n", getpid(), fd);
        strcpy(buffer, "这是子进程写入的数据\n");
        
        // 子进程先写入数据
        ssize_t bytes_write = write(fd, buffer, strlen(buffer));
        if(bytes_write == -1){
            perror("子进程write");
            close(fd);
            exit(EXIT_FAILURE);
        }
        printf("子进程%d写入数据成功\n", getpid());
        
        // 子进程关闭文件描述符
        close(fd);
        printf("子进程%d已关闭文件描述符\n", getpid());
        
        // 子进程尝试再次使用已关闭的文件描述符（这会失败）
        strcpy(buffer, "子进程关闭后再次尝试写入\n");
        ssize_t bytes_write2 = write(fd, buffer, strlen(buffer));
        if(bytes_write2 == -1){
            perror("子进程再次write");
            printf("子进程%d: 验证了关闭文件描述符后无法再次使用\n", getpid());
        }
        
    }else{
        //父进程代码
        printf("父进程%d: 文件描述符 fd = %d\n", getpid(), fd);
        sleep(5); // 等待子进程先执行
        
        // 父进程在子进程关闭文件描述符后继续使用
        strcpy(buffer, "这是父进程写入的数据\n");
        ssize_t bytes_write = write(fd, buffer, strlen(buffer));
        if(bytes_write == -1){
            perror("父进程write");
            close(fd);
            exit(EXIT_FAILURE);
        }
        printf("父进程%d在子进程关闭后仍然写入数据成功\n", getpid());
        
        // 父进程最后关闭文件描述符
        close(fd);
        printf("父进程%d已关闭文件描述符\n", getpid());
    }

    if(pid == 0){
        printf("子进程%d执行完毕\n", getpid());
    }else{
        printf("父进程%d执行完毕\n", getpid());
    }

    return 0;
}