#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "mymem.h"

int main()
{
    void *heap = sbrk(0);
    char *a = my_malloc(64);
    my_free(a);
    char *b = my_malloc(128);
    assert(b != a); // New block should not reuse freed smaller block
    my_free(b);
}
