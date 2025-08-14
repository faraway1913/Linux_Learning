#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * 线程执行函数
 * @param arg 线程参数（本例中未使用）
 * @return 线程返回值
 */
void *task(void *arg){
    printf("Thread started\n");    // 线程启动时输出信息
    sleep(2);                      // 模拟线程执行工作，休眠2秒钟
    printf("Thread finished\n");   // 线程完成工作时输出信息
    return NULL;                   // 线程正常结束
}

int main(){
    pthread_t tid;                 // 定义线程ID变量
    
    // 创建一个新线程
    // &tid: 存储新线程ID的地址
    // NULL: 使用默认线程属性
    // task: 线程要执行的函数
    // NULL: 传递给task函数的参数
    pthread_create(&tid, NULL, task, NULL);

    // 将线程设置为分离状态
    // 分离后的线程在结束时会自动释放资源，无需主线程调用pthread_join等待
    pthread_detach(tid);

    // 主线程继续执行自己的任务
    printf("Main thread continues\n");
    
    // 主线程休眠3秒
    // 注意：pthread_detach不会等待子线程结束
    // 如果主线程提前退出，整个进程会结束，分离的线程也会被强制终止
    // 因此需要确保主线程存活足够长时间以让子线程完成工作
    //需要注意的是， pthread_detach 不会等待子线程结束，如果在后者执行完毕之前主线程退出，则整个进程退出，子线程被强制终止。为了验证这一点，请注释下一行代码
    sleep(3);
    
    printf("Main thread ending\n");
    
    return 0;  // 主线程正常退出，程序结束
}


/*相关函数
1. pthread_detach函数
int pthread_detach(pthread_t thread);

@brief:
    将线程标记为 detached 状态。 POSIX 线程终止后，如果没有调用pthread_detach 或 pthread_join，其资源会继续占用内存，类似于僵尸进程的未回收状态。默认情况下创建线程后，它处于可 join 状态，此时可以调用 pthread_join 等待线程终止并回收资源。但是如果主线程不需要等待线程终止，可以将其标记为 detached状态，这意味着线程终止后，其资源会自动被系统回收。

@param:
    thread 线程 ID

@return:
    int 成功返回 0，失败返回错误码
*/