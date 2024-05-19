#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mymem.h"

int main(int argc, char *argv[])
{
    char *c = "hello world";
    char *pc = malloc(12);
    memcpy(pc, c, 12);
    printf("%s\n", pc);
    char *mc = my_malloc(12);
    memcpy(mc, c, 12);
    printf("%s\n", mc);
    return 0;
}