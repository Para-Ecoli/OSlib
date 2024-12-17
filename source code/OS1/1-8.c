#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/syscall.h>

// 共享变量
int shared_var = 0;

// 线程，使用system()
void* thread11(void* arg) {
    printf("thread1 tid = %d, pid = %d\n", syscall(SYS_gettid), getpid());
    system("./system_call");
    printf("thread1 system_call return\n");
    return NULL;
}

void* thread22(void* arg) {
    printf("thread2 tid = %d, pid = %d\n", syscall(SYS_gettid), getpid());
    system("./system_call");
    printf("thread2 system_call return\n");
    return NULL;
}

int main() {
    // 创建两个线程
    pthread_t thread1, thread2;

    // 创建线程1，执行increment函数
    if(pthread_create(&thread1, NULL, thread11, NULL) == 0)
        printf("thread1 create success!\n");

    // 创建线程2，执行decrement函数
    if(pthread_create(&thread2, NULL, thread22, NULL) == 0)
        printf("thread2 create success!\n");

    // 等待线程1结束
    pthread_join(thread1, NULL);

    // 等待线程2结束
    pthread_join(thread2, NULL);

    return 0;
}