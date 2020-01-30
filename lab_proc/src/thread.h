#ifndef THREAD_H
#define THREAD_H

#include "pch.h"

static int imaginary_stack;
static int dummy;

static pthread_mutex_t mtx;

static sem_t sem;

void init_thread_tu();

void* thread_signal_sync(void* notused);

void* sync_producer(void* notused);

void* sync_consumer(void* notused);

void threader();

#endif // THREAD_H
