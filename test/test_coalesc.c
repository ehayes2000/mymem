#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "mymem.h"

/*
    test that consequtive sequences are combined into larger chunks of memory
    1. malloc(64)   A (used, 64)

    2. malloc(64)   B (used, 64)

    3. free(A)      A (free, 64)
                    B (used, 64)

    4. free(A)      A(free, 128)

    5. malloc(128)  A(used, 128)
*/
int main()
{
    Block *head = sbrk(0);
    assert(head->next == NULL);
    // get mem
    void *A = my_malloc(64);
    Block *Ah = A - sizeof(Block);
    void *B = my_malloc(64);
    Block *Bh = B - sizeof(Block);
    assert(Ah->free == 0);
    assert(Bh->free == 0);
    assert(Ah->size == 64);
    assert(Bh->size == 64);
    // free A
    my_free(A);
    assert(Ah->free == 1);
    assert(Ah->size == 64);
    assert(head->next == Ah);
    assert(Ah->next == NULL);
    // free B
    my_free(B);
    assert(head->next == Ah);
    assert(Ah->next == NULL);
    assert(Bh->free == 1);
    assert(Ah->size == 128 + sizeof(Block)); // A and B should combine
    void *before = sbrk(0);
    my_malloc(128 + sizeof(Block));
    void *after = sbrk(0);
    assert(before == after);
    assert(Ah->size == 128 + sizeof(Block));
    assert(head->next == NULL);
    assert(Ah->next == NULL);
}
