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

void    free_wrong_addr(void)
{
    void    *ptr;

    ptr = malloc(100);
    free(ptr+1);
}

int     main(int ac, char *av[])
{
    free_prev();
    // free_wrong_addr();
    return (0);
}