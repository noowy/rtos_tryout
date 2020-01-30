#include "thread.h"

void init_thread_tu()
{
    pthread_mutex_init(&mtx, NULL);
    sem_init(&sem, 0, 0);
    imaginary_stack = 0;
    dummy = 0;
}

void* thread_signal_sync(void* notused)
{
    int tid = pthread_self();

    while (1)
    {
        pthread_mutex_lock(&mtx);
        if (dummy > 10)
            break;
        printf("This is thread #%d with dummy value %d \n", tid, dummy);
        ++dummy;
        pthread_mutex_unlock(&mtx);
    }
}

void* sync_producer(void* notused)
{
    while (1)
    {
        ++imaginary_stack; // maybe replace with atomic increment (?)
        printf("Produced a value, now %d\n", imaginary_stack);
        sem_post(&sem);
        sleep(2);
    }
}

void* sync_consumer(void* notused)
{
    while (1)
    {
        sleep(1);
        while (imaginary_stack == 0) sem_wait(&sem);
        --imaginary_stack;
        printf("Consumed a value, now %d\n", imaginary_stack);
    }
}

void threader()
{
    int i;
    char ch;

    for (i = 0; i < 10; ++i)
    {
        pthread_create(NULL, NULL, &thread_signal_sync, NULL);
    }

    pthread_create(NULL, NULL, &sync_consumer, NULL);
    pthread_create(NULL, NULL, &sync_producer, NULL);

    while (scanf("%c", &ch)) 
        if (ch == 'q') break;
    
    return;
}
