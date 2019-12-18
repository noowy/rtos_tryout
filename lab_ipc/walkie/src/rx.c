#include "rx.h"

void init_mthreading()
{
    msg_ready = false;
    pthread_mutex_init(&mtx);
    pthread_condvar_init(&condvar);
}

void atomic_msg_upd(const char* msg, int ipc_type) // replace signatures with void* ptr for pthread_create compatibility
{
    pthread_mutex_lock(&mtx);
    
    while (msg_ready) pthread_cond_wait(&condvar, &mtx); 
    
    free(g_msg.msg)
    g_msg.msg = (char)malloc(sizeof(char) * strlen(msg) + 1); // +1 for the null-terminator
    
    strcpy(msg, g_msg.msg);
    g_msg.ipc_type = ipc_type;
    
    ptread_mutex_unlock(&mtx);
}

void msg_receiver()
{
    int ch_id;

    ch_id = ChannelCreate(0);
    printf("Channel id is %d\n", ch_id);

    while (true)
    {
        // message receiving logic
    }
}

void fifo_receiver(const char* name)
{
    char buf[];
    FILE* fifo = fopen(name, "r");

    while(fgets(buf, 255, fifo))
        atomic_msg_upd(buf, IPC_FIFO);
}

void mqueue_receiver()
{

}

void sig_receiver()
{

}

void smem_receiver()
{

}

void sync_printer()
{
    while (true)
    {
        pthread_mutex_lock(&mtx);

        while (!msg_ready) pthread_cond_wait(&condvar, &mtx);

        printf("New message arrived at channel type %d:\n%s\n", g_msg.ipc_type, g_msg.msg);

        pthread_mutex_unlock(&mtx);
    }
}
