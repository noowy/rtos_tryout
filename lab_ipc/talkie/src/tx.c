#include "tx.h"

void msg_send(const char* data, int proc_id, int ch_id)
{   
    int conn_id;
    char reply[255];

    conn_id = ConnectAttach(0, proc_id, ch_id, 0, 0);
    MsgSend(conn_id, data, strlen(data) + 1, reply, sizeof(reply));
    ConnectDetach(conn_id);
}

void pipe_send(const char* data, const char* address)
{
    int pipe_ends[2];
    pipe(pipe_ends);

    const int fds = { pipe_ends[0], 1, 2};
    const char* argv[] = { "/home/qnxuser/rtos_tryout/lab_ipc/http_tx/http_tx.out", address};

    spawnp(
        "/home/qnxuser/rtos_tryout/lab_ipc/http_tx/http_tx.out", 
        3,
        fds,
        NULL,
        argv,
        NULL
    )

    FILE* output = fdopen(pipe_ends[1])
    fputs(output, data);
}

void fifo_send(const char* data, const char* address)
{
    FILE* fifo = fopen(address, 'w');
    fputs(fifo, data);
}

void mqueue_send(const char* data, const char* address)
{

}

void sig_send(int proc_id, int sig)
{
    kill(proc_id, sig);
}

void smem_send(const char* data, const char* address)
{
    int fd;
    char* shared;

    if (strlen(data) >= 511)
        data[511] = 0;
    
    fd = shm_open(address, O_RDWR, 0777);
    ftruncate(fd, strlen(data) + 1);

    shared = mmap(0, strlen(data) + 1, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    strcpy(shared, data);

    close(fd);
}

void sender()
{

}
