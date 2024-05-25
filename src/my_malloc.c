#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "mymem.h"

#define MIN_BLOCK_SIZE 1;

Block *head = NULL;

void *my_malloc(size_t b)
{
    if (b == 0)
    {
        return NULL;
    }
    if (head == NULL)
    {
        head = sbrk(sizeof(Block));
        head->size = 0;
        head->free = 0;
        head->next = NULL;
    }
    Block *prev = NULL;
    Block *record = head;
    while (record != NULL)
    {
        if (record->free == 1 && record->size > b + sizeof(Block))
        {
            Block *next = (char *)record + b + sizeof(Block);
            next->next = record->next;
            next->size = record->size - b - sizeof(Block);
            next->free = 1;
            record->next = NULL;
            record->free = 0;
            record->size = b;
            if (prev != NULL)
                prev->next = next;
            return (void *)record + sizeof(Block);
        }
        else if (record->free == 1 && record->size >= b)
        {
            if (prev != NULL)
                prev->next = record->next;
            record->free = 0;
            record->next = NULL;
            return (void *)record + sizeof(Block);
        }
        prev = record;
        record = record->next;
    }
    Block *p = (Block *)sbrk(b + sizeof(Block));
    if (p == -1)
    {
        return NULL;
    }
    p->free = 0;
    p->size = b;
    p->next = NULL;
    return ((void *)p) + sizeof(Block);
}

void my_free(Block *p)
{
    if (p == NULL || p < (void *)(head + 1))
    {
        fprintf(stderr, "Free on illegal region\n");
        exit(1);
    }

    Block *header = (Block *)p - 1;

    if (header->free == 1)
    {
        fprintf(stderr, "Double free\n");
        exit(1);
    }

    Block *record = head;
    Block *prev = NULL;

    // Find the correct position to insert the block back into the free list
    int iters = 0;
    while (record != NULL && record < header)
    {
        iters++;
        prev = record;
        record = record->next;
    }

    // Insert the block into the free list
    header->next = record;
    if (prev != NULL)
    {
        prev->next = header;
    }
    else
    {
        fprintf(stderr, "Lost your head?\n");
        exit(1);
    }

    header->free = 1;

    // Coalesce with previous block if possible
    if (prev != head && (char *)prev + prev->size + sizeof(Block) == (char *)header)
    {
        prev->size += header->size + sizeof(Block);
        prev->next = header->next;
    }

    // Coalesce with next block if possible
    if (record != NULL && (char *)header + header->size + sizeof(Block) == (char *)record)
    {
        header->size += record->size + sizeof(Block);
        header->next = record->next;
    }
}
