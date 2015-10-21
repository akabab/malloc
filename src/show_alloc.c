#include "malloc.h"

extern t_region		*g_heap[3];

static size_t	show_region_mem_ex(t_region *r, const char *type)
{
	t_region	*cur_region;
	t_block		*b;
	size_t		total_regions;
	size_t		total_bytes;

	total_bytes = 0;
	total_regions = 0;
	cur_region = r;
	ft_printf("\033[33m%s\033[0m : %p\n", type, cur_region);
	while (cur_region)
	{
		b = cur_region->block_list;
		while (b)
		{
			b->is_free ? ft_printf("\033[32m") : ft_printf("\033[31m");
			ft_printf("=%p==============\n", b->data);
			ft_printf("             %d bytes\n", b->size);
			ft_printf("=%p==============\n\033[0m", b->data + b->size);
			total_bytes += (!b->is_free) ? b->size : 0;
			b = b->next;
		}
		total_regions++;
		cur_region = cur_region->next;
	}
	return (total_bytes);
}

static size_t	show_region_mem(t_region *r, const char *type)
{
	t_region	*cur_region;
	t_block		*cur_block;
	size_t		total_bytes;

	total_bytes = 0;
	cur_region = r;
	ft_printf("%s : %p\n", type, cur_region);
	while (cur_region)
	{
		cur_block = cur_region->block_list;
		while (cur_block)
		{
			if (!cur_block->is_free)
			{
				ft_printf("%p - %p : %d octets\n", cur_block->data,
					cur_block->data + cur_block->size, cur_block->size);
				total_bytes += cur_block->size;
			}
			cur_block = cur_block->next;
		}
		cur_region = cur_region->next;
	}
	return (total_bytes);
}

void			show_alloc_mem_ex(void)
{
	int		i;
	char	*type;
	size_t	total_bytes;

	total_bytes = 0;
	i = 0;
	ft_printf("\n_/ HEAP \\_________\n");
	while (i < 3)
	{
		if (i == TINY)
			type = "TINY";
		if (i == SMALL)
			type = "SMALL";
		if (i == LARGE)
			type = "LARGE";
		total_bytes += show_region_mem_ex(g_heap[i], type);
		i++;
	}
	ft_printf("Total : %d bytes\n", total_bytes);
}

void			show_alloc_mem(void)
{
	int		i;
	char	*type;
	size_t	total_bytes;

	total_bytes = 0;
	i = 0;
	while (i < 3)
	{
		if (i == TINY)
			type = "TINY";
		if (i == SMALL)
			type = "SMALL";
		if (i == LARGE)
			type = "LARGE";
		total_bytes += show_region_mem(g_heap[i], type);
		i++;
	}
	ft_printf("Total : %d octets\n", total_bytes);
}
