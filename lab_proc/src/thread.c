#include "thread.h"

void init_mutex()
{
	mtx = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mtx, NULL);
}
