#ifndef PROC_H
#define PROC_H

#include "pch.h"

void spawn_proc(const char* proc_name);

void exec_proc(const char* proc_name);

void fork_proc(const char* proc_name);

void vfork_proc(const char* proc_name);

#endif // PROC_H
