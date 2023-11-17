#include <stdio.h>

int main() {
    FILE *out_file;
    char buf[] = "你好，这是用于命名管道示例的数据。\n";

    out_file = fopen("a_pipe", "w");

    if (out_file == NULL) {
        perror("打开文件时出错");
        return 1;
    }

    fprintf(out_file, "%s", buf);//使用 fprintf 函数将字符串 buf 写入打开的文件。

    fclose(out_file);

    return 0;
}

