#include "malloc.h"
#include <stdlib.h>

void    realloc_copy(void)
{
    void    *ptr[10];

    ptr[0] = malloc(20);
    ptr[1] = malloc(100);
    show_alloc_mem();
    realloc(ptr[0], 40);
    show_alloc_mem();
}

void    realloc_fusion(void)
{
    void    *ptr[10];

    ptr[0] = malloc(20);
    ptr[1] = malloc(120);
    ptr[2] = malloc(40);
    show_alloc_mem();
    free(ptr[1]);
    show_alloc_mem();
    realloc(ptr[0], 40);
    show_alloc_mem();
}

int     main(int ac, char *av[])
{
    // realloc_fusion();
    realloc_copy();
    return (0);
}