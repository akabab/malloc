#include "malloc.h"

#include <stdlib.h>

int     main(int ac, char *av[])
{
    int     i;
    void    *addr[ac];

    i = 1;
    while (i < ac)
    {
        printf("---malloc(%s)---\n", av[i]);
        addr[i] = malloc(atoi(av[i]));
        printf("---malloc(%s)---> %p\n", av[i], addr[i]);
        show_alloc_mem();
        printf("\n");
        i++;
    }
    // addr[1] += 1;
    printf("---free---> %p\n", addr[1]);
    free(addr[1]);
    show_alloc_mem();
    void *tmp = malloc(10);
    show_alloc_mem();
    free(tmp);
    show_alloc_mem();
    // printf("BLOCK_SIZE = %lu\n", sizeof(t_block));
    return (0);
}