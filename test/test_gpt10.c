#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "mymem.h"

int main()
{
    void *heap = sbrk(0);
    char *a = my_malloc(10);
    char *b = my_malloc(20);
    char *c = my_malloc(30);

    assert(heap + 2 * sizeof(Block) == a);
    assert(a + 10 + sizeof(Block) == b);
    assert(b + 20 + sizeof(Block) == c);

    my_free(b);
    char *d = my_malloc(20);
    assert(d == b); // Ensure reuse of freed block

    my_free(a);
    my_free(c);
    my_free(d);
}
