#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "mymem.h"

int main()
{
    void *heap = sbrk(0);
    char *a = my_malloc(40);
    my_free(a);
    char *b = my_malloc(40);
    assert(b == a); // ensure reuse of freed block
    my_free(b);
}
