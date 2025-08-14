#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * 线程执行函数，可以被取消
 * @param arg 线程参数（本例中未使用）
 * @return 线程返回值
 */
void *task(void *arg){
    printf("Thread started\n");           // 线程启动时输出信息
    
    // 默认取消类型为延迟取消（PTHREAD_CANCEL_DEFERRED），无需显式设置
    // 线程只有在遇到取消点时才会真正被取消
    
    // 模拟线程工作
    printf("Working...\n");               // 表示开始工作
    sleep(1);                             // 模拟工作过程，休眠1秒钟
    
    // pthread_testcancel() 是一个显式的取消点函数
    // 如果有取消请求，线程会在此处终止执行
    pthread_testcancel();                 // 检查是否有取消请求，如果有则终止线程
    
    // 如果线程未被取消，会继续执行到这里
    printf("After Cancelled\n");          // 线程未被取消时输出
    
    return NULL;                          // 线程正常结束
}

/**
 * 主函数
 */
int main(){ 
    pthread_t tid;                        // 线程标识符变量
    void *res;                            // 用于存储线程退出状态的变量
    
    // 创建一个新线程来执行task函数
    // &tid: 存储新线程ID的地址
    // NULL: 使用默认线程属性
    // task: 线程要执行的函数
    // NULL: 传递给task函数的参数
    pthread_create(&tid, NULL, task, NULL);

    // 请求取消子线程
    // pthread_cancel向指定线程发送取消请求
    // 成功返回0，失败返回非0值
    if (pthread_cancel(tid) != 0){
        perror("pthread_cancel");         // 如果取消操作失败，打印错误信息
    }
    
    // 等待子线程终止并获取其退出状态
    // pthread_join会阻塞直到指定线程结束
    // &res: 用于接收线程的退出状态
    pthread_join(tid, &res);
    
    // 检查子线程的退出状态，判断是否被取消
    if (res == PTHREAD_CANCELED){
        // 线程被成功取消
        printf("Thread was canceled\n");
    }else{
        // 线程未被取消，可能是正常结束或其他原因
        printf("Thread was not canceled, exit code: %ld\n", (long)res);
    }
    
    return 0;  // 程序正常退出
}



/*相关函数
1. pthread_cancel函数
int pthread_cancel(pthread_t thread);

@brief:
    向目标线程发送取消请求。目标线程是否和何时响应取决于它的取消状态和类型
        取消状态（Cancelability State）：可以是 enabled（默认）或 disabled。如果取消状态为禁用，则取消请求会被挂起，直至线程启用取消功能。如果取消状态为启用，则线程的取消类型决定它何时取消。
        取消类型（Cancelability Type）：可以是 asynchronous（异步）或 deferred（被推迟，默认值）。
            asynchronous：意味着线程可能在任何时候被取消（通常立即被取消，但系统并不保证这一点）
            deferred：被推迟意味着取消请求会被挂起，直至被取消的线程执行取消点（cancellation point）函数时才会真正执行线程的取消操作。
        取消点函数(此例中是pthread_testcancel())：是在 POSIX 线程库中专门设计用于检查和处理取消请求的函数。当被取消的线程执行这些函数时，如果线程的取消状态是 enabled 且类型是 deferred，则它会立即响应取消请求并终止执行。 man 7 pthreads 可以看到取消点函数列表。
@param:
    thread 目标线程，即被取消的线程
@return:
    int 成功返回 0，失败返回非零的错误码

需要注意的是，取消操作和 pthread_cancel 函数的调用是异步的，这个函数的返回值只能告诉调用者取消请求是否成功发送。当线程被成功取消后，通过pthread_join 和线程关联将会获得 PTHREAD_CANCELED 作为返回信息，这是判断取消是否完成的唯一方式
*/