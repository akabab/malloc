#include "malloc.h"

#include <stdlib.h>

int     main(int ac, char *av[])
{
    int     i;

    i = 1;
    while (i < ac)
    {
        printf("---malloc(%s)---\n", av[i]);
        malloc(atoi(av[i]));
        show_alloc_mem();
        printf("\n");
        i++;
    }
    // printf("BLOCK_SIZE = %lu\n", BLOCK_SIZE);
    return (0);
}