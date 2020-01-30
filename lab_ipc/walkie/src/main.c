#include "rx.h"

int main(int argc, char **argv)
{
<<<<<<< Updated upstream
    printf("The process ID is %d\n", getpid());
=======
    init_mthreading();
    sync_printer();
    start_receivers(argc, argv);
>>>>>>> Stashed changes
    return 0;
}
