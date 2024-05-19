#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include "mymem.h"

void *heap = NULL;
void *heap_end = NULL;

typedef struct
{
    size_t size;
    int free;
} Block;

void *my_malloc(size_t b)
{
    // get heap start
    if (heap == NULL)
    {
        heap = sbrk(0);
        heap_end = heap;
    }
    // memory should always start with a block
    Block *record = (Block *)heap;
    while (record < heap_end)
    {
        if (record->free && record->size <= b)
        {
            printf("filled record\n");
            record->free = 0;
            return record + sizeof(Block);
        }
        record += record->size;
    }
    void *p = sbrk(b + sizeof(Block));
    if (p == -1)
    {
        return NULL;
    }
    heap_end += b + sizeof(Block);
    Block header = {
        .size = b,
        .free = 0};
    *(Block *)p = header;
    return p + sizeof(Block);
}

void my_free(void *p)
{
    // TODO need some better error checking
    if (p >= sizeof(Block))
    {
        Block *header = (Block *)(p - sizeof(Block));
        header->free = 1;
    }
}