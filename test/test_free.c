#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "mymem.h"

int main()
{
    void *heap = sbrk(0);
    // malloc mem
    void *p = my_malloc(64);
    assert(heap + 2 * sizeof(Block) == p);
    // free mem
    my_free(p);
    void *end = sbrk(0);
    // malloc more mem and check that new mem has not been sbrk'd
    void *p2 = my_malloc(32);
    void *end2 = sbrk(0);
    assert(end == end2);
    printf("%p, %p\n", p, p2);
    assert(p2 == p);
}
