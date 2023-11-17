#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void main()
{
    int x, fd[2];//int x, fd[2];：定义整型变量和一个包含两个元素的整型数组，用于存储管道的文件描述符。
    char buf[30], s[30];//char buf[30], s[30];：定义两个字符数组，用于存储要传输的数。

    // 创建管道
    if (pipe(fd) == -1) {//pipe(fd);：创建管道，fd[0]用于读取，fd[1]用于写入。
        perror("pipe");
        return;
    }

    // 创建子进程
    while ((x = fork()) == -1);//while((x = fork())== -1);：使用fork创建子进程，如果创建失败则一直尝试。

    if (x == 0)//if(x==0)：在子进程中执行以下代码块。
    {
        // 子进程向管道写入数据
        sprintf(buf, "This is an example \n");//将字符串格式化并存储到buf数组中。
        if (write(fd[1], buf, 30) == -1) {//将数据写入管道。
            perror("write");
            return;
        }
    }
    else//在父进程中执行以下代码块。
    {
        // 父进程等待子进程执行完毕
        wait(NULL);//等待子进程执行完毕

        // 父进程从管道读取数据
        if (read(fd[0], s, 30) == -1) {//read(fd[0], s, 30);：从管道读取数据到s数组。
            perror("read");
            return;
        }

        // 打印从管道读取的数据
        printf("%s", s);
    }
}
/*
这个程序创建了一个子进程，子进程向管道写入一段字符串，而父进程从管道读取该字符串并打印出来。 */
