#include "tx.h"

void msg_send(char* data, char* address)
{   
    // maybe should take address const and put it into variable string
    int proc_id = atoi(strtok(address, ":"));
    int ch_id = atoi(strtok(NULL, ":"));

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

    const int fds[] = { pipe_ends[0], 1, 2 };
    const char* argv[] = { "/home/qnxuser/http_tx.out", address }; // probably need constant pointer to char

    spawnp(
        "/home/qnxuser/http_tx.out", 
        3,
        fds,
        NULL,
        argv,
        NULL
    );

    FILE* output = fdopen(pipe_ends[1], "w");
    fputs(data, output);
    fclose(output);
}

void fifo_send(const char* data, const char* address)
{
    FILE* fifo = fopen(address, "w");
    fputs(data, fifo);
    fclose(fifo);
}

void mqueue_send(const char* data, const char* address)
{
    mqd_t mqd = mq_open(address, O_WRONLY, NULL);
    mq_send(mqd, data, (strlen(data)+ 1), 0);
    mq_close(mqd);
}

void sig_send(const char* data, const char* address)
{
    int proc_id = atoi(address);
    int sig = atoi(data);

    kill(proc_id, sig);
}

void smem_send(const char* data, const char* address)
{
    int fd;
    char* shared;
    
    fd = shm_open(address, O_WRONLY, 0777);
    ftruncate(fd, strlen(data) + 1);

    shared = mmap(0, strlen(data) + 1, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    strcpy(shared, data);

    close(fd);
    shm_unlink(address);
}

void sender(int argc, char* argv[])
{
    char ch;

    while ((ch = getopt(argc, argv, "m:f:q:s:h:")) != -1)
    {
        switch (ch)
        {
            case 'm':
                msg_send(argv[3], optarg); // think about argument positioning and how exactly getopt works?
                break;
            case 'f':
                fifo_send(argv[3], optarg);
                break;
            case 'q':
                mqueue_send(argv[3], optarg);
                break;
            case 's':
                sig_send(argv[3], optarg);
                break;
            case 'h':
                smem_send(argv[3], optarg);
                break;
            case '?':
                return;
            default:
                abort();
        }
    }
}
