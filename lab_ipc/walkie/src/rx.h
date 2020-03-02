#ifndef RX_H
#define RX_H 
#include "pch.h"

int msg_ready;
static pthread_mutex_t mtx; 
static pthread_cond_t  condvar;

enum ipc_type { IPC_FIFO, IPC_MSG, IPC_MQUEUE, IPC_SIG, IPC_SMEM };

typedef struct 
{
    char *msg;
    int ipc_type;
} sync_ipc_msg;

static sync_ipc_msg g_msg;

void init_mthreading();

void atomic_msg_upd(const char* msg, int ipc_type);

void* msg_receiver(void* is_dissmised);

void* fifo_receiver(void* is_dissmised);

void* mqueue_receiver(void* is_dissmised);

void* sig_receiver(void* is_dissmised);

void* smem_receiver(void* is_dissmised);

void* sync_printer(void* notused);

void start_receivers(int argc, char* argv[]);

#endif // RX_H