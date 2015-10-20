#include "malloc.h"
#include <stdlib.h>

void    free_prev(void)
{
    void    *ptr[10];

    ptr[0] = malloc(20);
    ptr[1] = malloc(120);
    ptr[2] = malloc(40);
    show_alloc_mem();
    free(ptr[0]);
    show_alloc_mem();
    free(ptr[1]);
    show_alloc_mem();
    free(ptr[2]);
    show_alloc_mem();
}

int     main(int ac, char *av[])
{
    free_prev();
    return (0);
}