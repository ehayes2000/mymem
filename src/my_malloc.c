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
        head->free = 1;
        head->next = NULL;
    }
    Block *prev = NULL;
    Block *record = head;
    while (record != NULL)
    {
        printf("searching\n");
        if (record->free == 1 && record->size > b + sizeof(Block))
        {
            printf("found split\n");
            Block *next = record + b + sizeof(Block);
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
            printf("found \n");
            if (prev != NULL)
                prev->next = record->next;
            record->free = 0;
            record->next = NULL;
            return (void *)record + sizeof(Block);
        }
        prev = record;
        record = record->next;
    }
    printf("make\n");
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

void my_free(void *p)
{
    // TODO need some better error checking
    if (p == NULL || p < sizeof(Block))
        return;
    Block *header = (Block *)(p - sizeof(Block));
    if (header->free == 1)
    {
        fprintf(stderr, "Double free\n");
        exit(1);
    }
    Block *record = head;
    Block *prev = NULL;
    while (record != NULL && record <= header)
    {
        if (record == header)
        {
            fprintf(stderr, "How did we get here\n");
            exit(1);
        }
        prev = record;
        record = record->next;
    }
    if (prev != NULL)
    {
        prev->next = header;
        header->next = record;
    }
    else
    {
        prev = head->next; // use prev as temp
        head->next = header;
        header->next = prev;
    }
    header->free = 1;
}