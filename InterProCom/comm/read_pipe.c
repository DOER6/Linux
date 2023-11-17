#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *in_file;//声明一个文件指针
    char buf[80];

    in_file = fopen("a_pipe", "r");//使用 fopen 函数打开名为 "a_pipe" 的文件，以只读模式打开（"r"）

    if (in_file == NULL) {
        perror("打开文件时出错");
        exit(1);
    }

    while (fgets(buf, sizeof(buf), in_file) != NULL) {//使用 fgets 函数从打开的文件中读取一行数据，存储到 buf 中。循环进行读取，直到文件结束。
        printf("从管道中读取：%s", buf);
    }

    fclose(in_file);

    return 0;
}

