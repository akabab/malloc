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
        addr[i] = malloc(atoi(av[i]));
        // show_alloc_mem();
        i++;
    }
    show_alloc_mem();
    return (0);
}