#include "malloc.h"

#include <stdlib.h>

void    unmap_large(void)
{
    void    *ptr[10];

    ptr[0] = malloc(100000);
    ptr[1] = malloc(200000);
    ptr[2] = malloc(400000);
    show_alloc_mem();
    free(ptr[1]);
    show_alloc_mem();
    free(ptr[0]);
    show_alloc_mem();
    free(ptr[2]);
    show_alloc_mem();
}

void    unmap_tiny(void)
{
    void    *ptr[10];

    ptr[0] = malloc(100);
    ptr[1] = malloc(200);
    ptr[2] = malloc(400);
    show_alloc_mem();
    free(ptr[1]);
    show_alloc_mem();
    free(ptr[0]);
    show_alloc_mem();
    free(ptr[2]);
    show_alloc_mem();
    ptr[2] = malloc(900);
    show_alloc_mem();
    free(ptr[2]);
    show_alloc_mem();
}


int     main(int ac, char *av[])
{
    unmap_tiny();
    // unmap_large();
    return (0);
}