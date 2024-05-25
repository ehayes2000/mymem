#ifndef mymem_h
#define mymem_h
#include <stddef.h>
#include <unistd.h>

typedef struct
{
    size_t size;
    int free;
    struct Block *next;
} Block;

void *my_malloc(size_t);
void my_free(Block *p);
#endif