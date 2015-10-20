#include "malloc.h"

#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

int     get_limit(void)
{
    struct rlimit   rlim;
    int             ret;

    ret = getrlimit(RLIMIT_AS, &rlim);
    if (ret != -1)
        printf("rlim cur: %llu, max: %llu\n", rlim.rlim_cur, rlim.rlim_max);
    return (ret);
}

int     main(int ac, char *av[])
{
    int     i;
    void    *addr[ac];

    // get_limit();
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
    free(addr[2]);
    show_alloc_mem();
    void *tmp = malloc(10);
    show_alloc_mem();
    free(tmp);
    show_alloc_mem();
    // printf("BLOCK_SIZE = %lu\n", sizeof(t_block));
    return (0);
}