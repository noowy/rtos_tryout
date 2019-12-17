#ifndef THREAD_H
#define THREAD_H

#include "pch.h"

static int imaginary_stack;

static pthread_mutex_t mtx;

static sem_t sem;

void init_thread_tu();

void thread_signal(void* thread_id);

void thread_signal_sync(void* thread_id);

void sync_producer();

void sync_consumer();

#endif // THREAD_H
