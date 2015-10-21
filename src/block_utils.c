#include "malloc.h"

t_block		*get_block(void *ptr)
{
	char	*tmp;

	tmp = ptr;
	ptr = tmp - BLOCK_SIZE;
	return (ptr);
}

void		copy_data(t_block *src, t_block *dst)
{
	char		*src_data;
	char		*dst_data;
	size_t		i;

	src_data = src->data;
	dst_data = dst->data;
	i = 0;
	while (i < src->size && i < dst->size)
	{
		dst_data[i] = src_data[i];
		i++;
	}
}

t_block		*fusion_block(t_block *b)
{
	if (b->next && b->next->is_free)
	{
		b->size += BLOCK_SIZE + b->next->size;
		b->next = b->next->next;
		if (b->next)
			b->next->prev = b;
	}
	return (b);
}

void		split_block(t_block *b, size_t size)
{
	t_block		*new_b;

	new_b = new_block(b->data + size, b->size - size - BLOCK_SIZE);
	new_b->prev = b;
	new_b->next = b->next;
	b->size = size;
	b->next = new_b;
	if (new_b->next)
		new_b->next->prev = new_b;
}

t_block		*new_block(void *at, size_t size)
{
	t_block		*b;

	b = (t_block *)at;
	b->size = size;
	b->prev = NULL;
	b->next = NULL;
	b->is_free = TRUE;
	b->ptr = b->data;
	return (b);
}
