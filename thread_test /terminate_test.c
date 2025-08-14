#include<pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#include <string.h>
//定义结果结构体
typedef struct Result{
    char *p;
    int len;
} Result;
/**
* 红玫瑰
*
* void *argv: 指针，可以传递的参数 这里用一个字符表示她的代号
* return: void* 结果结构体指针 返回结局
*/
void *red_thread(void *argv)
{
    Result *result = malloc(sizeof(Result));
    char code = *((char *)argv);
    // 存放回信
    char *ans = malloc(101);
    while (1){
        fgets(ans,100,stdin);
        if (ans[0]==code){
            //接收到了对应的信息
            free(ans);
            printf("红玫瑰离开了!\n");
            char *redAns = strdup("红玫瑰独自去了纽约.\n");
            result->p = redAns;
            result->len = strlen(redAns);
            // 结束线程 输出返回值
            pthread_exit((void *)result);
        }else{
            printf("红玫瑰还在等你!\n");
        }
    }
}

/**
* 白玫瑰
*
* void *argv: 指针，可以传递的参数 这里用一个字符表示她的代号
* return: void* 结果结构体指针 返回结局
*
*/
void *white_thread(void *argv)
{
    Result *result = malloc(sizeof(Result));
    char code = *((char *)argv);
    // 存放回信
    char *ans = malloc(101);
    while (1){
        fgets(ans,100,stdin);
        if (ans[0]==code){
            //接收到了对应的信息
            free(ans);
            printf("白玫瑰离开了!\n");
            char *redAns = strdup("白玫瑰独自去了伦敦.\n");
            result->p = redAns;
            result->len = strlen(redAns);
            // 结束线程 输出返回值
            pthread_exit((void *)result);
        }else{
            printf("白玫瑰还在等你!\n");
        }
    }
}


int main()
{
    // 声明线程标识符
    pthread_t pid_red;
    pthread_t pid_white;

    // 设置角色代号
    char red_code='r';
    char white_code='w';

    // 声明结果指针
    Result *red_result = NULL;
    Result *white_result = NULL;
    
    // 创建两个线程,红玫瑰,白玫瑰
    pthread_create(&pid_red, NULL, red_thread, &red_code);
    pthread_create(&pid_white, NULL, white_thread, &white_code);

    // 等待红玫瑰线程结束并获取结果
    pthread_join(pid_red, (void **)&red_result);
    printf("红玫瑰故事结局:%s\n",red_result->p);

    // 释放红玫瑰线程分配的内存
    free(red_result->p);
    free(red_result);
    
    // 等待白玫瑰线程结束并获取结果
    pthread_join(pid_white, (void **)&white_result);
    printf("白玫瑰故事结局:%s\n",white_result->p);
    
    // 释放白玫瑰线程分配的内存
    free(white_result->p);
    free(white_result);

    return 0;
}



/*相关函数
1. pthread_join函数
int pthread_join(pthread_t thread, void **retval);

@brief:
    等待指定线程结束， 获取目标线程的返回值，并在目标线程结束后回收它的资源

@param:
    pthread_t thread: 指定线程 ID
    void **retval: 这是一个可选参数，用于接收线程结束后传递的返回值。如果非空，pthread_join 会在成功时将线程的 exit status 复制到 *retval 所指向的内存位置。如果线程没有显式地通过 pthread_exit 提供返回值，则该参数将被设为 NULL 或忽略
    return: int 
        成功 0
        失败 1


2. pthread_exit函数
void pthread_exit(void *retval);

@brief:
    结束关闭调用该方法的线程，并返回一个内存指针用于存放结果

@param:
    void *retval: 要返回给其它线程的数据
*/