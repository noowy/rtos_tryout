#include "proc.h"

void spawn_proc(const char* proc_name)
{

}

void exec_proc(const char* proc_name)
{
	int retval;

	retval = execl(proc_name, proc_name, NULL);

	if (retval == -1)
		printf("Something went wrong\n");
	return;
}

void fork_proc(const char* proc_name)
{
	int child_pid;

	child_pid = fork();
	if (child_pid == 0)
		printf("This was printed by child %d\n", getpid());
		exec_proc(proc_name);
	else
		printf("This was printed by parent %d\n", getpid());

	return;
}

void vfork_proc(const char* proc_name)
{
	int child_pid;

	child_pid = vfork();
	if (child_pid == 0)
	{
		printf("This is a child process %d\n", getpid());
		exec_proc(proc_name);
	}
	else
		printf("Ok the child (%d) must be gone by now, it's me, parent %d\n", child_pid, getpid());
	return;
}
