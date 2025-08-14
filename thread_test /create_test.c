#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define BUF_LEN 1024

char *buf;

/**
 * @brief 线程input_thread读取标准输入的数据,放入缓存区
 * 
 * @param argv不需要输入参数,所以固定为NULL
 * @return void* 也不需要返回值
 */

 void *input_thread(void *argv){
    int i = 0;
    while(1){
        //从标准输入读取一个字符
        char c = fgetc(stdin);
        //如果字符不为0也不是换行,写入缓存区
        if(c && c!='\n'){
            buf[i++] = c;
            //缓存区索引溢出,i归零
            if(i >= BUF_LEN){
                i = 0;
            }
        }
    }
 }


 /**
  * @brief 线程output_thread将缓存区数据写到到标准输出,每个字符换行
  * 
  * @param  argv不需要输入参数,所以固定为NULL
  * @return void* 也不需要返回值
  * 
  */


void *output_thread(void *argv){
    int i = 0;
    while(1){
        if(buf[i]){
            //从缓冲区读取一个字节写入标准输出并换行
            fputc(buf[i], stdout);
            fputc('\n', stdout);

            //清理读取完毕的字节
            buf[i++] = 0;
            if(i >= BUF_LEN){
                i = 0;
            }
        }else{
            sleep(1);
        }
    }
}


int main(){ 
    pthread_t pid_input;
    pthread_t pid_output;
    //分配缓存
    buf = malloc(BUF_LEN);

    //初始化缓存区
    for(int i = 0; i < BUF_LEN; i++){
        buf[i] = 0;
    }

    //创建读取线程
    pthread_create(&pid_input, NULL, input_thread, NULL);

    //创建写出线程
    pthread_create(&pid_output, NULL, output_thread, NULL);

    //等待指定线程结束,详细作用后续讲解
    pthread_join(pid_input, NULL);
    pthread_join(pid_output, NULL);

    free(buf);

    return 0;
}



/*线程创建相关函数
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void*(*start_routine)(void *), void *arg);

@brief
    创建一个新线程

@param 
    pthread_t *thread: 指向线程标识符的指针,线程创建成功时,用于存储新创建线程的线程标识符
    const pthread_attr_t *attr: pthead_attr_t 结构体,这个参数可以用来设置线程的属性,如优先级、栈大小等。如果不需要定制线程属性,可以传入 NULL,此时线程将采用默认属性。
    void *(*start_routine)(void *): 一个指向函数的指针,它定义了新线程开始执行时的入口点。这个函数必须接受一个 void * 类型的参数,并返回 void * 类型的结果
    void *arg: start_routine 函数的参数,可以是一个指向任意类型数据的指针
    return: int 线程创建结果
        0: 线程创建成功
        非0: 线程创建失败

*/