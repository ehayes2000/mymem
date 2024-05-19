#ifndef mymem_h
#define mymem_h
#include <stddef.h>
#include <unistd.h>

void *my_malloc(size_t);
void my_free(void *p);
#endif