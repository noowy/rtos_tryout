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

sync_ipc_msg g_msg;

void init_mthreading();

void* atomic_msg_upd(void *msg_data_raw);

void msg_receiver();

void fifo_receiver(const char* name);

void mqueue_receiver(const char* name);

void sig_receiver();

void smem_receiver(const char* name);

void sync_printer();

void start_receivers(int argc, char* argv[]);

#endif // RX_H