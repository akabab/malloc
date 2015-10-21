#include "malloc.h"

#include <stdlib.h>

int     main(int ac, char *av[])
{
    int     i;

    i = 0;
    printf("---120 x malloc(%d)---\n", TINY_BLOCK_MAX_SIZE-1);
    while (i < 120)
    {
        malloc(TINY_BLOCK_MAX_SIZE-1);
        i++;
    }
    show_alloc_mem();
    return (0);
}