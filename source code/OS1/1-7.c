#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

// 共享变量
int shared_var = 0;

// 信号量
sem_t semaphore;

// 线程1的操作函数：对共享变量加100，重复100,000次
void* increment(void* arg) {
    for (int i = 0; i < 100000; i++) {
        sem_wait(&semaphore);  // 等待信号量（P操作）
        shared_var += 100;
        sem_post(&semaphore);  // 释放信号量（V操作）
    }
    return NULL;
}

// 线程2的操作函数：对共享变量减100，重复100,000次
void* decrement(void* arg) {
    for (int i = 0; i < 100000; i++) {
        sem_wait(&semaphore);  // 等待信号量（P操作）
        shared_var -= 100;
        sem_post(&semaphore);  // 释放信号量（V操作）
    }
    return NULL;
}

int main() {
    // 初始化信号量，初始值为1（表示资源可用）
    sem_init(&semaphore, 0, 1);

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

    // 销毁信号量
    sem_destroy(&semaphore);

    // 输出共享变量的最终值
    printf("Final value of shared variable: %d\n", shared_var);

    return 0;
}