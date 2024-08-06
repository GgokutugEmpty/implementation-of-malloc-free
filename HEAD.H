#ifndef HEAD_H
#define HEAD_H
#include <stdint.h>
#include <stddef.h>
void print_memory_status(const char *message);
void *malloc(size_t size);
void free(void *ptr);
#endif /*HEAD.H*/