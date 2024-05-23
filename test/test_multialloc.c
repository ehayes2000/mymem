#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "mymem.h"

/*
make two calls to my_malloc
check that header blocks are correct
check that correct memory is allocated
*/

int main()
{
    void *heap = sbrk(0);
    char *george = my_malloc(7);
    char *henry = my_malloc(6);
    assert(heap + 2 * sizeof(Block) == george);
    Block *b = george - sizeof(Block);
    assert(b->size == 7);
    assert(b->next == NULL);
    assert(b->free == 0);
    Block *c = henry - sizeof(Block);
    assert(c->size == 6);
    assert(c->free == 0);
    assert(b->next == NULL);
    strncpy(george, "george\0", 7);
    strncpy(henry, "henry\0", 6);
    printf("%p\n", george);
    printf("[%s]\n", henry);
    printf("[%s]\n", george);
    printf("%p\n", george);
    assert(c->size == 6);
    assert(c->free == 0);
    assert(b->next == NULL);
    assert(b->size == 7);
    assert(b->next == NULL);
    assert(b->free == 0);
    my_free(george);
    my_free(henry);
    assert(b->free == 1);
    assert(c->free == 1);
    Block *head = (Block *)heap;
    assert(head->next == b);
    assert(b->next == c);
    assert(c->next == NULL);
}
