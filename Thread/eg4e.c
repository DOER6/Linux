#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

int buf = 0;
pthread_mutex_t mutex_x = PTHREAD_MUTEX_INITIALIZER;
sem_t sem;

void *computeThread()
{
    int i = 0;
    while (1)
    {
        pthread_mutex_lock(&mutex_x);
        while (buf != 0)
        {
            pthread_mutex_unlock(&mutex_x);
            sched_yield();
            pthread_mutex_lock(&mutex_x);
        }
        buf = i;
        printf("Computing buf=%d...", buf);
        i++;
        pthread_mutex_unlock(&mutex_x);
        sem_post(&sem);
    }
    return NULL;
}

void *printThread()
{
    while (1)
    {
        sem_wait(&sem);
        pthread_mutex_lock(&mutex_x);
        printf("buf=%d\n", buf);
        buf = 0;
        pthread_mutex_unlock(&mutex_x);
    }
    return NULL;
}

int main()
{
    sem_init(&sem, 0, 0);
    pthread_t thread1_id, thread2_id;

    pthread_create(&thread2_id, NULL, &printThread, NULL);
    pthread_create(&thread1_id, NULL, &computeThread, NULL);

    pthread_join(thread1_id, NULL);
    pthread_join(thread2_id, NULL);

    return 0;
}

