#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * 线程执行函数，可以被异步取消
 * @param arg 线程参数（本例中未使用）
 * @return 线程返回值
 */
void *task(void *arg){
    printf("Thread started\n");                    // 线程启动时输出信息
    
    // 设置取消类型为异步取消（PTHREAD_CANCEL_ASYNCHRONOUS）
    // 异步取消允许线程在任何时间点被取消，而不仅限于取消点
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    
    // 模拟线程工作
    printf("Working...\n");                        // 表示开始工作
    sleep(1);                                      // 模拟工作过程，休眠1秒钟
    
    // 在异步取消模式下，线程可能在任何时刻被取消
    // 如果取消发生在sleep之后，会执行到这里
    printf("After Cancelled\n");                   // 线程未被取消时输出
    
    return NULL;                                   // 线程正常结束
}

/**
 * 主函数
 */
int main(){
    pthread_t tid;                                 // 线程标识符变量
    void *res;                                     // 用于存储线程退出状态的变量
    
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
        perror("pthread_cancel");                  // 如果取消操作失败，打印错误信息
    }
    
    // 等待子线程终止并获取其退出状态
    // pthread_join会阻塞直到指定线程结束
    // &res: 用于接收线程的退出状态
    pthread_join(tid, &res);
    
    // 检查子线程的退出状态，判断是否被取消
    if (res == PTHREAD_CANCELED){
        // 线程被成功取消
        printf("Thread was canceled\n");
    }
    else{
        // 线程未被取消，可能是正常结束或其他原因
        printf("Thread was not canceled, exit code: %ld\n", (long)res);
    }
    
    return 0;                                      // 程序正常退出
}



/*相关函数
1. pthread_setcanceltype
int pthread_setcanceltype(int type, int *oldtype);

@brief: 
    设置调用线程的取消类型
        PTHREAD_CANCEL_DEFERRED：设置取消类型为推迟
        PTHREAD_CANCEL_ASYNCHRONOUS：设置取消类型为异步

@param:
    type 目标类型
    oldtype 指针，用于接收历史类型

@return:
    int 成功返回 0，失败返回非零错误码

*/