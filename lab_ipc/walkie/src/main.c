#include "rx.h"

int main(int argc, char **argv)
{
    printf("The process ID is %d\n", getpid());
    init_mthreading();
    pthread_create(NULL, NULL, &sync_printer, NULL);
    start_receivers(argc, argv);
    return 0;
}
