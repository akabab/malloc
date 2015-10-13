#include "malloc.h"

t_region		*g_heap[3];// = {NULL, NULL, NULL};
int	g_test = 0;

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

void		ft_putstr(char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

void		show_region_mem(t_region *region_list, char *type_str)
{
	t_region	*cur_region;
	t_block		*cur_block;

	cur_region = region_list;
	printf("%s : %p\n", type_str, cur_region); // ft_
	while (cur_region)
	{
		cur_block = cur_region->block_list;
		while (cur_block)
		{
			printf("===============\n");
			printf(" s: %zu      \n", cur_block->size);
			printf("===============\n");
			cur_block = cur_block->next;
		}
		cur_region = cur_region->next;
	}
}

void		show_alloc_mem(void)
{
	int		i;
	char	*type_str;

	i = 0;
	while (i < 3)
	{
		if (i == TINY)
			type_str = "TINY";
		if (i == SMALL)
			type_str = "SMALL";
		if (i == LARGE)
			type_str = "LARGE";
		show_region_mem(g_heap[i], type_str);
		i++;
	}
}

void		free(void *ptr);
void		*realloc(void *ptr, size_t size);

int			get_region_type(size_t size)
{
	if (size < TINY_BLOCK_MAX_SIZE)
		return (TINY);
	if (size < SMALL_BLOCK_MAX_SIZE)
		return (SMALL);
	return (LARGE);
}

size_t		get_region_size(t_region_type type, size_t size)
{
	if (type == TINY)
		return (TINY_REGION_SIZE);
	else if (type == SMALL)
		return (SMALL_REGION_SIZE);
	else if (type == LARGE)
		return (size_t)((size / PAGE_SIZE) + 1) * PAGE_SIZE;
	else
		return (0);

	// size_t		region_size;
	// size_t		block_size;

	// if (type == TINY)
	// 	block_size = TINY_BLOCK_MAX_SIZE;
	// else if (type == SMALL)
	// 	block_size = SMALL_BLOCK_MAX_SIZE;
	// // else if (type == LARGE)
	// 	// block_size = LARGE_BLOCK_MAX_SIZE;
	// else
	// 	return 0;
	// region_size = (block_size + BLOCK_META_SIZE) * 100;
	// printf("region_size: %zu\n", region_size);
	// return region_size;
}

void		malloc_init(void)
{
	g_heap[0] = NULL;
	g_heap[1] = NULL;
	g_heap[2] = NULL;
}

// t_block		*new_block(size_t size)
// {
// 	t_block		*block;

// 	block->size = size;
// 	block->prev = NULL;
// 	block->next = NULL;
// 	block->is_free = TRUE;
// 	return block;
// }

t_region	*new_region(t_region_type type, size_t size)
{
	int			prot;
	int			flags;
	t_region	*region;

	prot = PROT_READ | PROT_WRITE;
	flags = MAP_ANON | MAP_PRIVATE;
	region = mmap(0, size, prot, flags, -1, 0);
	if (region == MAP_FAILED)
	{
		/* errno contains error */
		return NULL;
	}
	region->type = type;
	region->size = size - REGION_META_SIZE;
	region->next = NULL;

	// init first block
	t_block		*new_block;

	new_block = (t_block *)(region + REGION_META_SIZE);
	new_block->size = region->size - BLOCK_META_SIZE;
	new_block->prev = NULL;
	new_block->next = NULL;
	new_block->is_free = TRUE;

	printf("NEW Block : %p\n", new_block);
	region->block_list = new_block;

	printf("NEW REGION : %p\n", region);
	return region;
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

void		*malloc(size_t size)
{
	// malloc_init();
	// size check
	int		region_type;
	size_t	region_size;

	region_type = get_region_type(size);
	region_size = get_region_size(region_type, size);
	// printf("region_size: %zu\n", region_size);

	// check for free space
	t_region	*region_list;
	region_list = g_heap[region_type];
	if (region_list != NULL /* && region_list->max_contiguous_free_space >= size */)
	{
		printf("Yes REGION\n");
		// add block
		t_block * b = get_free_block(region_list, size);
		if (b)
		{
			//
		}
	}
	else
	{
		printf("No REGION : %d\n", region_type);
		// add region
		if (region_size == 0)
			return (NULL);
		g_heap[region_type] = new_region(region_type, region_size);
			// add block
	}
	printf("HEAP: [%p][%p][%p]\n", g_heap[0], g_heap[1], g_heap[2]);
	return (NULL);
}
