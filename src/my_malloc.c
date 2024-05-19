#include <unistd.h>
#include <stddef.h>
#include "mymem.h"

void *heap = NULL;
void *heap_end = NULL;

typedef struct
{
    size_t size;
    int free;
    void *data;
} Block;

void *my_malloc(size_t b)
{
    if (heap == NULL)
    {
        heap = sbrk(0);
        heap_end = heap;
    }
    void *p = sbrk(b + sizeof(Block));
    if (p == -1)
    {
        return NULL;
    }
    Block header = {
        .size = b,
        .free = 0,
        .data = p + sizeof(Block)};
    *(Block *)p = header;
    return header.data;
}