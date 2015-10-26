#include "malloc.h"

extern t_region				*g_heap[3];
extern pthread_mutex_t		g_mutex;

static void		*realloc_bycopy(void *ptr, t_block *b, size_t size)
{
	void		*new_p;
	t_block		*new_b;

	new_p = malloc_exec(size);
	if (!new_p)
		return (NULL);
	new_b = get_block(new_p);
	copy_data(b, new_b);
	free_exec(ptr);
	return (new_p);
}

static void		*handle_realloc(void *ptr, size_t size)
{
	t_block		*b;

	b = get_block(ptr);
	if (b->size >= size)
	{
		if ((b->size - size) >= BLOCK_SIZE)
			split_block(b, size);
	}
	else
	{
		if (b->next && b->next->is_free
			&& (b->size + BLOCK_SIZE + b->next->size) >= size)
		{
			fusion_block(b);
			if (b->size - size >= BLOCK_SIZE)
				split_block(b, size);
		}
		else
			return (realloc_bycopy(ptr, b, size));
	}
	return (ptr);
}

void			*realloc(void *ptr, size_t size)
{
	void	*addr;

	pthread_mutex_lock(&g_mutex);
	addr = NULL;
	if (!ptr)
		addr = malloc_exec(size);
	if (get_valid_region(ptr))
		addr = handle_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (addr);
}
