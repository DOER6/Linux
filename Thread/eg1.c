#include <pthread.h>
#include <stdio.h>

/* 定义打印函数：打印x 到stderr（标准错误输出—会显示在终端上）. */
void* print_xs(void* unused)
{
    while (1)
        fputc('x', stderr);
    return NULL;
}

/* 主程序. */
int main()
{
    pthread_t thread_id;

    /* 创建一个新线程. 新线程执行print_xs函数. */
    pthread_create(&thread_id, NULL, print_xs, NULL);

    /* 主进程连续打印o到stderr. */
    while (1)
        fputc('o', stderr);

    return 0;
}

