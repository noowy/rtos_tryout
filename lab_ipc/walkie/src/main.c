#include "rx.h"

int main(int argc, char **argv)
{
    printf("The process ID is %d\n", getpid());
    init_mthreading();
    sync_printer();
    start_receivers(argc, argv);
    return 0;
}
