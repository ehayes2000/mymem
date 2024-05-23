#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "mymem.h"

int main()
{
    void *heap = sbrk(0);
    char *a = my_malloc(128);
    my_free(a);
    char *b = my_malloc(64);
    assert(b == a); // Ensure reuse of freed block

    char *c = my_malloc(64);
    assert(c == b + 64 + sizeof(Block)); // Check if the block was split correctly

    my_free(b);
    my_free(c);
}
