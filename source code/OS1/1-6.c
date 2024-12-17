#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// 共享变量
int shared_var = 0;

// 线程1的操作函数：对共享变量加100，重复100,000次
void* increment(void* arg) {
    for (int i = 0; i < 100000; i++) {
        shared_var += 100;
    }
    return NULL;
}

// 线程2的操作函数：对共享变量减100，重复100,000次
void* decrement(void* arg) {
    for (int i = 0; i < 100000; i++) {
        shared_var -= 100;
    }
    return NULL;
}

int main() {
    // 创建两个线程
    pthread_t thread1, thread2;

    // 创建线程1，执行increment函数
    if(pthread_create(&thread1, NULL, increment, NULL) == 0)
        printf("thread1 create success!\n");

    // 创建线程2，执行decrement函数
    if(pthread_create(&thread2, NULL, decrement, NULL) == 0)
        printf("thread2 create success!\n");

    // 等待线程1结束
    pthread_join(thread1, NULL);

    // 等待线程2结束
    pthread_join(thread2, NULL);

    // 输出共享变量的最终值
    printf("Final value of shared variable: %d\n", shared_var);

    return 0;
}