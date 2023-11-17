#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>

void main() {
    int i, r, p1, p2, fd[2];
    char buf[50], s[50];

    // 创建管道
    pipe(fd);

    // 创建第一个子进程 (p1)
    while ((p1 = fork()) == -1);
    if (p1 == 0) {
        // 在子进程 p1 中锁定写入管道的文件描述符
        lockf(fd[1], 1, 0);//锁定整个文件，以确保在写入数据到管道的时候，不会被其他进程同时写入。
        
        // 向管道中写入消息
        sprintf(buf, "child process p1 is sending messages!\n");
        printf("child process p1!\n");
        write(fd[1], buf, 50);
        
        // 等待5秒
        sleep(5);

        // 解锁文件描述符
        lockf(fd[1], 0, 0);

        // 子进程 p1 退出
        exit(0);
    } else {
	waitpid(p1,NULL,0);
        // 创建第二个子进程 (p2)
        while ((p2 = fork()) == -1);
        if (p2 == 0) {
            // 在子进程 p2 中锁定写入管道的文件描述符
            lockf(fd[1], 1, 0);
            
            // 向管道中写入消息
            sprintf(buf, "child process p2 is sending messages\n");
            printf("child process p2!\n");
            write(fd[1], buf, 50);
            
            // 等待5秒
            sleep(5);

            // 解锁文件描述符
            lockf(fd[1], 0, 0);

            // 子进程 p2 退出
            exit(0);
	    
        } else {
            // 等待第一个子进程 p1 结束
            wait(0);

            // 从管道中读取数据到缓冲区 s
            if ((r = read(fd[0], s, 50)) == -1)
                printf("can't read pipe\n");
            else
                printf("%s\n", s);

            // 等待第二个子进程 p2 结束
            wait(0);

            // 再次从管道中读取数据到缓冲区 s
            if ((r = read(fd[0], s, 50)) == -1)
                printf("can't read pipe\n");
            else
                printf("%s\n", s);

            // 父进程退出
            exit(0);
        }
    }
}

