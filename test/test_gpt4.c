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
    Block *ab = (Block *)a - 1;
    printf("ab->free %d, ab->size %d", ab->free, ab->size);
    assert(ab->size == 2 * sizeof(Block) + 20 + 30 + 10);

    char *d = my_malloc(10);
    Block *eb = d + 10;
    printf("eb->free %d, eb->size %d", eb->free, eb->size);
    char *e = my_malloc(20);
    char *f = my_malloc(30);

    printf("a + 10 + block %p\n", a + 10 + sizeof(Block));
    printf("a - d %p == %p\n", a, d);
    printf("b - e %p == %p\n", b, e);
    printf("c - f %p == %p\n", c, f);
    assert(d == a);
    assert(e == b);
    assert(f == c);

    my_free(d);
    my_free(e);
    my_free(f);
}
