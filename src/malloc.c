#include "malloc.h"

t_region			*g_heap[3] = {NULL};
pthread_mutex_t		g_mutex = PTHREAD_MUTEX_INITIALIZER;

void		*malloc_exec(size_t size)
{
	t_region	*region;
	int			region_type;
	t_block		*block;

	region_type = get_region_type(size);
	region = g_heap[region_type];
	if (region)
	{
		block = region_alloc(region, size);
		if (!block)
			return (NULL);
	}
	else
	{
		block = extend_region(&g_heap[region_type], size);
		if (!block)
			return (NULL);
	}
	return (block->data);
}

void		*malloc(size_t size)
{
	void	*addr;

	pthread_mutex_lock(&g_mutex);
	addr = malloc_exec(size);
	pthread_mutex_unlock(&g_mutex);
	return (addr);
}
