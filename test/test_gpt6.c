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

    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);

    char *large_block = my_malloc(1024 * 1024 * 1024); // Try allocating 1GB
    assert(large_block == NULL);                       // Likely to fail on most systems

    my_free(a);
    my_free(b);
    my_free(c);
}
