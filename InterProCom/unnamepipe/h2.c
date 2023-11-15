#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int s[10];
    pid_t pid;

    // 主进程写入0到9的数字
    for (int i = 0; i < 10; i++) {
        s[i] = i;
    }

    // 创建子进程
    pid = fork();

    if (pid == -1) {
        // 错误处理
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // 子进程读取并显示数组中的数字
        printf("Child process reading values:\n");
        for (int i = 0; i < 10; i++) {
            printf("%d ", s[i]);
        }
        printf("\n");

        // 子进程退出
        exit(EXIT_SUCCESS);
    } else {
        // 等待子进程结束
        wait(NULL);

        // 主进程显示写入成功
        printf("Main process wrote values successfully.\n");
    }

    return 0;
}

