#include "malloc.h"

int			get_region_type(size_t size)
{
	if (size < TINY_BLOCK_MAX_SIZE)
		return (TINY);
	if (size < SMALL_BLOCK_MAX_SIZE)
		return (SMALL);
	return (LARGE);
}

size_t		get_region_size(size_t size)
{
	if (size < TINY_BLOCK_MAX_SIZE)
		return (TINY_REGION_SIZE);
	else if (size < SMALL_BLOCK_MAX_SIZE)
		return (SMALL_REGION_SIZE);
	return (size_t)((size / PAGE_SIZE) + 1) * PAGE_SIZE;
}

t_region	*get_last_region(t_region *region)
{
	t_region	*cur_region;

	cur_region = region;
	while (cur_region && cur_region->next)
		cur_region = cur_region->next;
	return (cur_region);
}

t_block		*extend_region(t_region **region, size_t size)
{
	t_region	*new_r;
	t_region	*last;
	t_block		*new_b;

	last = get_last_region(*region);
	new_r = new_region(get_region_type(size), get_region_size(size));
	if (!new_r)
		return (NULL);
	new_b = new_block(new_r->data, 0);
	if (get_region_type(size) == LARGE)
		new_b->size = size;
	else
	{
		new_b->size = new_r->size - BLOCK_SIZE;
		if (new_b->size > size && (new_b->size - size) >= BLOCK_SIZE)
			split_block(new_b, size);
	}
	new_b->is_free = FALSE;
	new_r->block_list = new_b;
	new_r->prev = last;
	if (last)
		last->next = new_r;
	else
		*region = new_r;
	return (new_b);
}

t_region	*new_region(t_region_type type, t_region_size size)
{
	t_region	*region;
	int			prot;
	int			flags;

	prot = PROT_READ | PROT_WRITE;
	flags = MAP_ANON | MAP_PRIVATE;
	region = mmap(0, size, prot, flags, -1, 0);
	if (region == MAP_FAILED)
	{
		ft_perror("mmap error");
		return (NULL);
	}
	region->size = size - REGION_SIZE;
	region->type = type;
	region->prev = NULL;
	region->next = NULL;
	region->block_list = NULL;
	return (region);
}
