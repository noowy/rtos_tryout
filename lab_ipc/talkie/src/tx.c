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
