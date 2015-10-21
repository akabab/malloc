#include "malloc.h"
#include <stdlib.h>

int		main(int ac, char *av[])
{
	int			i;
	size_t		x;
	size_t		size;

	i = 0;
	x = atoi(av[1]);
	size = atoi(av[2]);
	printf("%lu * malloc(%lu)...\n", x, size);
	while (i < x)
	{
		malloc(size);
		i++;
	}
	// show_alloc_mem_ex();
	return (0);
}