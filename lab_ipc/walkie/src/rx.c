#include "rx.h"

void init_mthreading()
{
    msg_ready = 0;
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&condvar, NULL);
}

void atomic_msg_upd(const char* msg, int ipc_type)
{
    pthread_mutex_lock(&mtx);
    
    while (msg_ready) pthread_cond_wait(&condvar, &mtx); 

    free(g_msg.msg);
    g_msg.msg = (char*)malloc(sizeof(char) * (strlen(msg) + 1)); // +1 for the null-terminator
    
    strcpy(g_msg.msg, msg);
    g_msg.ipc_type = ipc_type;
    
    msg_ready = 1;
    pthread_cond_signal(&condvar);
    pthread_mutex_unlock(&mtx);
}

void* msg_receiver(void* is_dissmised)
{
    int* dissmised = (int*) is_dissmised;

    int ch_id;
    int rcv_id;
    
    char msg[255];
    char reply[] = "you may go now";

    ch_id = ChannelCreate(0);
    printf("Channel id is %d\n", ch_id);

    if (ch_id == -1)
    {
        printf("%s\n", strerror(errno));
        return NULL;
    }

    while (1)
    {
        if (*dissmised)
        {
            ChannelDestroy(ch_id);
            return;
        }

        rcv_id = MsgReceive(ch_id, msg, sizeof(msg), NULL);

        atomic_msg_upd(msg, IPC_MSG);

        MsgReply(rcv_id, EOK, reply, sizeof(reply));
    }
}

void* fifo_receiver(void* is_dissmised) // check why blocks after receiving one msg
{
    int* dissmised = (int*) is_dissmised;    
    const char* name = "bitchin_fifo";

    if ( mkfifo(name, S_IRUSR | S_IWUSR | S_IWOTH | S_IWGRP) == -1 )
    {
        printf("%s\n", strerror(errno));
        return NULL;
    }

    char buf[256];
    FILE* fifo = fopen(name, "r");

    while(1)
    {
        if (*dissmised)
        {
            fclose(fifo);
            return NULL;
        }

        if (fgets(buf, 255, fifo))
        {
            atomic_msg_upd(buf, IPC_FIFO);
        }
    }
}

void* mqueue_receiver(void* is_dissmised)
{
    int* dissmised = (int*) is_dissmised;
    const char* name = "/bitchin_mq";

    char msg[512];

    mqd_t mqd = mq_open(name, O_RDONLY | O_CREAT | O_NONBLOCK, S_IRUSR | S_IWUSR, NULL);

    if (mqd == -1)
    {
        printf("%s\n", strerror(errno));
        return NULL;
    }

    while (1)
    {
        if (*dissmised)
        {
            mq_close(mqd);
            return;
        }

        mq_receive(mqd, msg, sizeof(msg), NULL);
    }
}

void* sig_receiver(void* is_dissmised)
{
    int* dissmised = (int*) is_dissmised;

    char buf[128];

    int sig;
    sigset_t signals[] = { 20, 30 };

    while (1)
    {
        if(dissmised)
        {
            // probably change to a different logic without waiting in other func
            return;
        }

        sigwait(signals, &sig);

        atomic_msg_upd(itoa(sig, buf, 10), IPC_SIG);
    }
}

void* smem_receiver(void* is_dissmised)
{
    int* dissmised = (int*) is_dissmised;
    const char* name = "bitchin_smem";

    int fd;
    char* shared;

    const size_t buf_size = 512;
    char buf[buf_size];

    fd = shm_open(name, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);

    if (fd == -1)
    {
        printf("%s\n", strerror(errno));
        return NULL;
    }

    ftruncate(fd, buf_size);
    shared = mmap(0, buf_size, PROT_READ, MAP_SHARED, fd, 0);

    while (1)
    {
        if (*dissmised)
        {
            close(fd);
            shm_unlink(name);
            return;
        } 

        // if (!strcmp(buf, shared))
        //     continue;

        memcpy(buf, shared, buf_size);

        buf[buf_size - 1] = '\0';
        
        atomic_msg_upd(buf, IPC_SMEM); 
    }

}

void* sync_printer(void* notused)
{
    while (1)
    {
        pthread_mutex_lock(&mtx);

        while (!msg_ready) pthread_cond_wait(&condvar, &mtx);

        printf("New message arrived at channel type %d:\n%s\n", g_msg.ipc_type, g_msg.msg);

        msg_ready = 0;
        pthread_cond_signal(&condvar);
        pthread_mutex_unlock(&mtx);
    }
}

void start_receivers(int argc, char* argv[])
{
    char ch;
    int quit_sig = 0;

    while ((ch = getopt(argc, argv, "mfqsh")) != -1)
    {
        switch (ch)
        {
            case 'm':
            {
                puts("Launching message receiver");
                pthread_create(NULL, NULL, &msg_receiver, &quit_sig);
                break;
            }
            case 'f':
            {
                puts("Launching fifo receiver");
                pthread_create(NULL, NULL, &fifo_receiver, &quit_sig);
                break;
            }
            case 'q':
            {
                puts("Launching mqueue receiver");
                pthread_create(NULL, NULL, &mqueue_receiver, &quit_sig);
                break;
            }
            case 's':
            {
                puts("Launching signal receiver");
                pthread_create(NULL, NULL, &sig_receiver, &quit_sig);
                break;
            }
            case 'h':
            {
                puts("Launching shared memory receiver");
                pthread_create(NULL, NULL, &smem_receiver, &quit_sig);
                break;
            }
            case '?':
                return;
            default:
                abort();
        }
    }

    while (scanf("%c", &ch)) 
    {
        if (ch == 'q')
        {
            quit_sig = 1;
            sleep(2); // yes i know i should join them but do you know how many classes i still have to finish
            break;
        }
    }

    return;
}
