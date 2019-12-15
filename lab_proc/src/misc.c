#include "misc.h"

void thread_signal(void* thread_id)
{
	int tid = *((int*)thread_id);
	int dummy = 0;
	for (dummy = 0; dummy < 10; ++dummy)
	{
		printf("This is thread #%d with dummy value %d \n", tid, dummy);
	}
}

void thread_signal_sync(void* thread_id)
{
	int tid = *((int*)thread_id);
	int dummy = 0;
	for (dummy = 0; dummy < 10; ++dummy)
	{
		pthread_mutex_lock(mtx);
		printf("This is thread #%d with dummy value %d \n", tid, dummy);
		pthread_mutex_unlock(mtx);
	}
}
