#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "mymem.h"

/*
    test that correct amount of memory is being allocated
*/

int main()
{
    void *heap = sbrk(0);
    void *o = my_malloc(64);
    void *next = sbrk(0);
    printf("Heap initialized at %p\n", heap);
    printf("Testing offset at %p\n", o);
    assert(heap + 2 * sizeof(Block) == o);
    assert(next == o + 64);
    assert(next == heap + 64 + 2 * sizeof(Block));
    strncpy(o, "hello world\0", 12);
    printf("[%s]\n", o);
    return 0;
}
