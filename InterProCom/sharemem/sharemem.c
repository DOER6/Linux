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
/*
共享内存是一种进程间通信的机制，允许多个进程共享同一块内存区域。其基本原理如下：

1. **创建共享内存：** 使用系统调用 `shmget` 来创建一个共享内存段。在这个调用中，需要指定一个唯一的标识符，共享内存的大小，以及一些权限标志。如果共享内存已经存在，可以使用 `IPC_CREAT` 标志来创建或获取已存在的共享内存。
2. **附加共享内存：** 通过 `shmat` 系统调用，将共享内存段附加到进程的地址空间。这个调用返回一个指向共享内存的指针，通过该指针可以直接访问共享内存。
3. **进程间通信：** 进程可以通过直接读写共享内存的方式进行通信。由于多个进程共享同一块内存，一个进程写入的数据可以被其他进程读取。因此，共享内存是一种高效的进程间通信方式，特别适用于大量数据需要频繁传递的场景。
4. **分离共享内存：** 进程使用完共享内存后，通过 `shmdt` 系统调用将共享内存从自己的地址空间分离。这并不会删除共享内存段，只是将它从进程的地址空间中剥离出来。
5. **删除共享内存：** 当所有使用共享内存的进程都分离后，可以使用 `shmctl` 系统调用，标志为 `IPC_RMID`，来删除共享内存段。这样系统会释放相应的资源。

总体来说，共享内存的原理是通过在内核中创建一块共享区域，然后将这块共享区域映射到各个进程的地址空间中，使得这些进程可以直接访问共享的内存，从而实现数据共享和通信。*/


