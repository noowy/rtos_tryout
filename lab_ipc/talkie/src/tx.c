#include "tx.h"

void msg_send(const char* data, const char* address)
{

}

void pipe_send(const char* data, const char* address)
{
    int pipe_ends[2];
    pipe(pipe_ends);

    const int fds = { pipe_ends[0], 1, 2};
    char* const argv[] = { "/home/qnxuser/rtos_tryout/lab_ipc/http_tx/http_tx.out", address};

    spawnl(
        "/home/qnxuser/rtos_tryout/lab_ipc/http_tx/http_tx.out", 
        3,
        fds
    )
}

void fifo_send(const char* data, const char* address)
{
    FILE* fifo = fopen(address, 'w');
    fputs(fifo, data);
}

void mqueue_send(const char* data, const char* address)
{

}

void sig_send(const char* data, const char* address)
{

}

void smem_send(const char* data, const char* address)
{

}

void sender()
{

}
