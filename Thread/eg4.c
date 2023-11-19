#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

int buf = 0; // 全局变量 buf 用于存储数据
pthread_mutex_t mutex_x = PTHREAD_MUTEX_INITIALIZER; // 互斥锁
sem_t sem; // 信号量

// 生产者线程，计算并存储数据
void *computeThread()
{
    int i = 1;
    while (1)
    {
        pthread_mutex_lock(&mutex_x);
        while (buf != 0)
        {
            //sem_wait(&sem);
            //buf = i;
            //printf("Computing buf=%d...\n", buf);
            //sem_post(&sem);
	    pthread_mutex_unlock(&mutex_x);
        }
	buf=i;
        //i++;
	printf("Comuting buf =%d...\n",buf);
	i++;
        //if (i > 1000000)
            //i = 1;
        pthread_mutex_unlock(&mutex_x);
	sem_post(&sem);
    }
    return NULL;
}

// 消费者线程，打印数据
void *printThread()
{
    while (1)
    {
        pthread_mutex_lock(&mutex_x);
        while (buf > 0)
        {
            sem_wait(&sem);
            printf("buf=%d\n", buf);
            buf = 0;
            sem_post(&sem);
        }
        pthread_mutex_unlock(&mutex_x);
    }
    return NULL;
}

int main()
{
    sem_init(&sem, 0, 1); // 初始化信号量
    pthread_t thread1_id, thread2_id;

    // 创建两个线程
    pthread_create(&thread2_id, NULL, &printThread, NULL);
    pthread_create(&thread1_id, NULL, &computeThread, NULL);

    // 等待两个线程结束
    pthread_join(thread1_id, NULL);
    pthread_join(thread2_id, NULL);

    return 0;
}

