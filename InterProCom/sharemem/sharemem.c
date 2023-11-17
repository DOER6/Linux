#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int segment_id;
    char *shared_memory;
    struct shmid_ds shmbuffer;
    int segment_size;
    const int shared_segment_size = 0x6400;//声明变量，其中 segment_id 是共享内存的标识符，shared_memory 是指向共享内存的指针，shmbuffer 是用于获取共享内存信息的结构体，segment_size 存储共享内存的大小，shared_segment_size 是指定的共享内存大小。  

    /* Allocate a shared memory segment. */
    segment_id = shmget(IPC_PRIVATE, shared_segment_size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    //shmget 函数创建共享内存段
    //IPC_PRIVATE 生成一个唯一的标识符，
    //shared_segment_size 共享内存的大小，
    //IPC_CREAT 创建共享内存段，
    //IPC_EXCL 如果已存在同样大小的共享内存段则返回错误，
    //S_IRUSR | S_IWUSR 为用户赋予读写权限。

    /* Attach the shared memory segment. */
    shared_memory = (char*)shmat(segment_id, 0, 0);//使用 shmat 函数将共享内存段附加到进程的地址空间。shared_memory 指向共享内存段的起始地址。
    printf("shared memory attached at address %p\n", (void *)shared_memory);

    /* Determine the segment's size. */
    shmctl(segment_id, IPC_STAT, &shmbuffer);//使用 shmctl 函数获取共享内存的信息，包括大小，存储在 shmbuffer 结构体中。
    segment_size = shmbuffer.shm_segsz;
    printf("segment size: %d\n", segment_size);

    int p;
    while ((p = fork()) == -1);

    if (p == 0) {
        /* In the child process: Write a string to the shared memory segment. */
        sprintf(shared_memory, "Hello, world. I enjoy sharing memory!");
        printf("write\n");
    } else {
        wait(0);
        printf("read info from shared mem: %s\n", shared_memory);
    }

    /* Detach the shared memory segment. */
    shmdt(shared_memory);

    /* Deallocate the shared memory segment. */
    shmctl(segment_id, IPC_RMID, 0);

    return 0;
}

