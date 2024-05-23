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

    my_free(b);
    my_free(a);
    my_free(c);

    char *d = my_malloc(10);
    char *e = my_malloc(20);
    char *f = my_malloc(30);

    assert(d == a);
    assert(e == b);
    assert(f == c);

    my_free(d);
    my_free(e);
    my_free(f);
}
