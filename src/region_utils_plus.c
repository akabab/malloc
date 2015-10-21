#include "malloc.h"

extern t_region		*g_heap[3];

void		free_region(t_region *r)
{
	if (r->prev)
		r->prev->next = r->next;
	else
		g_heap[r->type] = r->next;
	if (r->next)
		r->next->prev = r->prev;
	else if (!r->prev)
		g_heap[r->type] = NULL;
	if (munmap(r, r->size + REGION_SIZE) == -1)
	{
		ft_perror("munmap error");
		exit(-1);
	}
}

t_block		*get_free_block(t_region *region, size_t size)
{
	t_region	*cur_region;
	t_block		*cur_block;

	cur_region = region;
	while (cur_region)
	{
		cur_block = cur_region->block_list;
		while (cur_block)
		{
			if (cur_block->is_free && cur_block->size >= size)
			{
				return (cur_block);
			}
			cur_block = cur_block->next;
		}
		cur_region = cur_region->next;
	}
	return (NULL);
}

t_region	*get_valid_region(void *ptr)
{
	int			i;
	t_region	*cur_r;
	t_block		*b;
	char		*tmp;

	b = get_block(ptr);
	tmp = (char *)b;
	i = 0;
	while (i < 3)
	{
		cur_r = g_heap[i];
		while (cur_r)
		{
			if (tmp >= cur_r->data && tmp <= (cur_r->data + cur_r->size))
			{
				if (b->ptr == ptr)
					return (cur_r);
			}
			cur_r = cur_r->next;
		}
		i++;
	}
	return (NULL);
}

void		*region_alloc(t_region *region, size_t size)
{
	t_block		*b;

	b = get_free_block(region, size);
	if (b)
	{
		if ((b->size - size) >= BLOCK_SIZE)
			split_block(b, size);
		b->is_free = FALSE;
		return (b);
	}
	else
	{
		b = extend_region(&region, size);
		return (b);
	}
	return (NULL);
}
