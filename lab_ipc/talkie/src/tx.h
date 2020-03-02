#ifndef TX_H
#define TX_H

#include "pch.h"

void msg_send(char* data, char* address);

void pipe_send(const char* data, const char* address);

void fifo_send(const char* data, const char* address);

void mqueue_send(const char* data, const char* address);

void sig_send(const char* data, const char* address);

void smem_send(const char* data, const char* address);

void sender(int argc, char* argv[]);

#endif // TX_H