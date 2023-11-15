#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>
#define ADDRESS (0x0)

int main() {
    char *mem_pointer;
    int f, i, p;

    if ((f = open("/dev/mem", O_RDWR)) < 0) {
        printf("Error opening /dev/mem\n");
        return 0;
    }

    mem_pointer = (char *)mmap(0, 8192, PROT_READ | PROT_WRITE, MAP_SHARED, f, ADDRESS);

    while ((p = fork()) == -1);

    if (p == 0) {
        printf("write data to mem\n");
        mem_pointer[0] = 2;
        mem_pointer[1] = 2;
    } else {
        wait(0);
        printf("read data from mem: %d %d\n", mem_pointer[0], mem_pointer[1]);
    }

    // close up:
    munmap(mem_pointer, 8192);
    close(f);

    return 0;
}

