#include "proc.h"
#include "misc.h"
#include "thread.h"

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        processor(argv[1], argv[2]);
	    return 0;
    }

    init_thread_tu();
    threader();
    return 0;
}
