#include "malloc.h"

t_region		*g_heap[3] = {NULL};

void		free(void *ptr)
{
	t_block		*b;
	t_region	*r;

	if (!ptr)
		return ;
	if ((r = get_valid_region(ptr)) != NULL)
	{
		b = get_block(ptr);
		b->is_free = TRUE;
		if (b->prev && b->prev->is_free)
			b = fusion_block(b->prev);
		if (b->next && b->next->is_free)
			fusion_block(b);
		if (!b->next && !b->prev)
		{
			if (r->type == LARGE || (r->prev || r->next))
				free_region(r);
		}
	}
}

void		*realloc_bycopy(void *ptr, t_block* b, size_t size)
{
	void		*new_p;
	t_block		*new_b;

	new_p = malloc(size);
	if (!new_p)
		return (NULL);
	new_b = get_block(new_p);
	copy_data(b, new_b);
	free(ptr);
	return (new_p);
}

void		*handle_realloc(void *ptr, size_t size)
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
			return realloc_bycopy(ptr, b, size);
	}
	return (ptr);
}

void		*realloc(void *ptr, size_t size)
{
	if (!ptr)
		return (malloc(size));
	if (get_valid_region(ptr))
		return handle_realloc(ptr, size);
	return (NULL);
}

void		*malloc(size_t size)
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
