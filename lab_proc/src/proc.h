#include <process.h>
#include <sys/types.h>

void spawn_proc(const char* proc_name);

void exec_proc(const char* proc_name);

void fork_proc(const char* proc_name);

void vfork_proc(const char* proc_name);