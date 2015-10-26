#include "malloc.h"

int     main(int ac, char *av[])
{
    void        *addr;
    t_block     *b;

    addr = malloc(50);
    b = addr - BLOCK_SIZE;
    printf("block: %p, size: %lu\n", b, b->size);
    show_alloc_mem_ex();
    return (0);
}