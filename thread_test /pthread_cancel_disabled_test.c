#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * 线程执行函数，取消功能被禁用
 * @param arg 线程参数（本例中未使用）
 * @return 线程返回值
 */
void *task(void *arg){
    printf("Thread started\n");                    // 线程启动时输出信息
    
    // 禁用线程取消功能
    // PTHREAD_CANCEL_DISABLE 禁止线程响应取消请求
    // 在此状态下，即使收到取消请求也会被挂起，直到重新启用取消功能
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    printf("Thread CancelState is disabled\n");    // 提示取消功能已被禁用
    
    // 设置取消类型为异步取消（PTHREAD_CANCEL_ASYNCHRONOUS）
    // 注意：即使设置了异步取消，但由于取消状态被禁用，线程仍不会被取消
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    
    // 模拟线程工作
    printf("Working...\n");                        // 表示开始工作
    sleep(1);                                      // 模拟工作过程，休眠1秒钟
    
    // 由于取消功能被禁用，即使主线程发送了取消请求，线程仍会执行到这里
    printf("After Cancelled\n");                   // 线程完成工作后输出
    
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
    // 但由于子线程禁用了取消功能，这个请求会被挂起
    if (pthread_cancel(tid) != 0){
        perror("pthread_cancel");                  // 如果取消操作失败，打印错误信息
    }
    
    // 等待子线程终止并获取其退出状态
    // pthread_join会阻塞直到指定线程结束
    // &res: 用于接收线程的退出状态
    pthread_join(tid, &res);
    
    // 检查子线程的退出状态
    if (res == PTHREAD_CANCELED){
        // 线程被成功取消（但在这个例子中不会发生）
        printf("Thread was canceled\n");
    }
    else{
        // 线程未被取消，正常结束
        printf("Thread was not canceled, exit code: %ld\n", (long)res);
    }
    
    return 0;                                      // 程序正常退出
}



/*相关函数
1. pthread_setcancelstate
@brief:
    设置调用线程的取消状态
        PTHREAD_CANCEL_ENABLE：启用取消功能
        PTHREAD_CANCEL_DISABLE：禁用取消功能

@param:
    state 目标状态
    oldstate 指针，用于返回历史状态
    
@return:
    int 成功返回 0，失败返回非零错误码
    
*/