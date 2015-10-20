#include "malloc.h"

extern t_region		*g_heap[3];

// void		show_region_mem(t_region *region_list, char *type_str)
// {
// 	t_region	*cur_region;
// 	t_block		*cur_block;
// 	size_t		total_regions;
// 	size_t		total_bytes;

// 	total_bytes = 0;
// 	total_regions = 0;
// 	cur_region = region_list;
// 	printf(C(YELLOW)"%s"C(NO)" : %p\n", type_str, cur_region); // ft_
// 	while (cur_region)
// 	{
// 		printf(CB(BLUE)"...< %p >....................\n"C(NO), cur_region);
// 		cur_block = cur_region->block_list;
// 		while (cur_block)
// 		{
// 			if (cur_block->is_free)
// 				printf(C(GREEN));
// 			else
// 				printf(C(RED));
// 			printf("===============\n");
// 			printf(" %p (%p) - %zu bytes\n", cur_block, cur_block->data, cur_block->size);
// 			printf("===============\n"C(NO));
// 			if (!cur_block->is_free)
// 				total_bytes += cur_block->size;
// 			cur_block = cur_block->next;
// 		}
// 		printf(CB(BLUE)"...> %p <....................\n"C(NO), cur_region->data + cur_region->size);
// 		total_regions++;
// 		cur_region = cur_region->next;
// 	}
// 	printf(C(YELLOW)"%s"C(NO)" - %zu bytes (%zu regions)\n", type_str, total_bytes, total_regions); // ft_
// }

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