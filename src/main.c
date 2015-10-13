#include "malloc.h"

int     main(int ac, char *av[])
{
    malloc(50);
    malloc(70);
    malloc(1400);
    malloc(23000);
    show_alloc_mem();
    return (0);
}