#include "http_comm.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        puts("Nah dude forgot the address");
        return 0;
    }
    post_data(argv[1]);
    return 0;
}