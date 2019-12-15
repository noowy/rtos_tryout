#ifndef MISC_H
#define MISC_H

#include "pch.h"
#include "thread.h"

void thread_signal(void* thread_id);

void thread_signal_sync(void* thread_id);

#endif // MISC_H
