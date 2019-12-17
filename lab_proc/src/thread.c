#include "thread.h"

void init_thread_tu()
{
    pthread_mutex_init(&mtx, NULL);
    sem_init(&sem, NULL)
    imaginary_stack = 0;
}

void thread_signal(void* thread_id)
{
    int tid = *((int*)thread_id);
    int dummy;
    for (dummy = 0; dummy < 10; ++dummy)
    {
        printf("This is thread #%d with dummy value %d \n", tid, dummy);
    }
}

void thread_signal_sync(void* thread_id)
{
    int tid = *((int*)thread_id);
    int dummy;
    for (dummy = 0; dummy < 10; ++dummy)
    {
        pthread_mutex_lock(mtx);
        printf("This is thread #%d with dummy value %d \n", tid, dummy);
        pthread_mutex_unlock(mtx);
    }
}

void sync_producer()
{
    while (true)
    {
        ++imaginary_stack; // maybe replace with atomic increment (?)
        printf("Produced a value, now %d\n", imaginary_stack);
        sem_post(&sem);
        sleep(1000);
    }
}

void sync_consumer()
{
    while (true)
    {
        sleep(500);
        while (imaginary_stack == 0) sem_wait(&sem);
        --imaginary_stack;
        printf("Consumed a value, now %d\n", imaginary_stack);
    }
}
