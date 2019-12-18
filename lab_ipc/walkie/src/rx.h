#ifndef RX_H
#define RX_H 
#include "pch.h"

bool msg_ready;
static pthread_mutex_t mtx; 
static pthread_cond_t  condvar;

enum ipc_type { IPC_FIFO, IPC_MSG, IPC_MQUEUE, IPC_SIG, IPC_SMEM };

typedef struct sync_ipc_msg
{
    char *msg;
    int ipc_type;
} g_msg;

void init_mthreading();

void atomic_msg_upd(const char* msg, int ipc_type);

void msg_receiver();

void pipe_receiver(const char* name);

void fifo_receiver();

void mqueue_receiver();

void sig_receiver();

void smem_receiver();

void printer();

#endif // RX_H