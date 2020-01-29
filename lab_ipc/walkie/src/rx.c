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
    
    msg_ready = true;
    pthread_cond_signal(&condvar);
    ptread_mutex_unlock(&mtx);
}

void msg_receiver()
{
    int ch_id;
    int rcv_id;
    char msg[255];
    char reply[] = "you may go now";
    sync_ipc_msg s_msg;

    ch_id = ChannelCreate(0);
    printf("Channel id is %d\n", ch_id);

    while (1)
    {
        rcv_id = MsgReceive(ch_id, msg, sizeof(msg), NULL);
        
        s_msg.msg = msg;
        s_msg.ipc_type = IPC_MSG;
        atomic_msg_upd((void*)s_msg);
        
        MsgReply(rcv_id, EOK, reply, sizeof(reply));
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
    sync_ipc_msg s_msg;

    int sig;
    sigset_t signals[] = { 20, 30 };

    while (1)
    {
        sigwait(signals, &sig);

        s_msg.msg = itoa(sig);
        s_msg.ipc_type = IPC_SIG;

        atomic_msg_upd((void*)s_msg);
    }
}

void smem_receiver()
{
    int fd;
    char* shared;

    fd = shm_open("/stuff", O_RDONLY | O_CREAT, 0777)

    shared = mmap(0, 512, PROT_READ, MAP_SHARED, fd, 0)

    while (1)
    {
        // think how to check whether new info arrived
    }
}

void sync_printer()
{
    while (1)
    {
        pthread_mutex_lock(&mtx);

        while (!msg_ready) pthread_cond_wait(&condvar, &mtx);

        printf("New message arrived at channel type %d:\n%s\n", g_msg.ipc_type, g_msg.msg);

        msg_ready = false;
        pthread_cond_signal(&condvar);
        pthread_mutex_unlock(&mtx);
    }
}
