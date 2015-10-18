#include "malloc.h"

t_region		*g_heap[3] = {NULL};//, NULL, NULL};
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
	size_t		total_bytes;

	total_bytes = 0;
	cur_region = region_list;
	printf(C(YELLOW)"%s"C(NO)" : %p\n", type_str, cur_region); // ft_
	while (cur_region)
	{
		printf(CB(BLUE)"...< %p >....................\n"C(NO), cur_region);
		cur_block = cur_region->block_list;
		while (cur_block)
		{
			if (cur_block->is_free)
				printf(C(GREEN));
			else
				printf(C(RED));
			printf("===============\n");
			printf(" %p - %zu bytes\n", cur_block, cur_block->size);
			printf("===============\n"C(NO));
			if (!cur_block->is_free)
				total_bytes += cur_block->size;
			cur_block = cur_block->next;
		}
		printf(CB(BLUE)"...> %p <....................\n"C(NO), cur_region);
		cur_region = cur_region->next;
	}
	printf(C(YELLOW)"%s"C(NO)" - %zu bytes\n", type_str, total_bytes); // ft_
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

size_t		get_region_size(size_t size)
{
	if (size < TINY_BLOCK_MAX_SIZE)
		return (TINY_REGION_SIZE);
	else if (size < SMALL_BLOCK_MAX_SIZE)
		return (SMALL_REGION_SIZE);
	return (size_t)((size / PAGE_SIZE) + 1) * PAGE_SIZE;
}

// __/DEBUG\__
void		DBG_sub_ptr(void *ptr1, void *ptr2, char *msg)
{
	if (msg)
		printf("%s : ", msg);
	printf("%ld bytes\n", ptr1 - ptr2);
}

t_block		*add_block_at(void *at, size_t size)
{
	t_block		*block;

	block = (t_block *)at;
	block->size = size;
	block->prev = NULL;
	block->next = NULL;
	block->is_free = TRUE;
	return (block);
}

t_region	*new_region(t_region_type type, t_region_size size)
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

	printf("NEW REGION : %p\n", region);

	// init first block
	region->block_list = add_block_at((void *)region + REGION_META_SIZE, region->size - BLOCK_META_SIZE);
	// printf("NEW Block : %p\n", region->block_list);
	// DBG_sub_ptr(region->block_list, region, "region meta");
;

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

t_region	*get_last_region(t_region *region)
{
	t_region	*cur_region;

	cur_region = region;
	while (cur_region->next)
		cur_region = cur_region->next;
	return (cur_region);
}

void		*region_alloc(t_region *region, size_t size)
{
	t_block *b = get_free_block(region, size);
	if (b)
	{
		printf("found free block: %p (%zu)\n", b, b->size);

		// SPLIT

		// create new free block right after IF enough space
		// at (void *)b + BLOCK_META_SIZE + size
		t_block *new_b = NULL;
		if (b->size - size > BLOCK_META_SIZE)
		{
			printf("HERE -----------------\n");

			new_b = (t_block *)((void *)b + BLOCK_META_SIZE + size);
			new_b->size = b->size - size - BLOCK_META_SIZE;
			new_b->prev = NULL; // b
			new_b->next = NULL;
			new_b->is_free = TRUE;
		}
		else
		{
			// new region
			printf("SPLIT :not enough space for new block\n");
			printf("NEW REG -----------------\n");
			(get_last_region(region))->next = new_region(get_region_type(size), get_region_size(size));
		}

		// ADD BLOCK
		b->size = size;
		b->prev = NULL;
		b->next = NULL;
		b->is_free = FALSE;

		if (new_b)
			b->next = new_b;

		// return block address
		return ((void *)b + BLOCK_META_SIZE);
	}
	else
	{
		printf("no free block\n");
		printf("NEW REG -----------------\n");
		(get_last_region(region))->next = new_region(get_region_type(size), get_region_size(size));
		region_alloc(region, size);
	}
	return (NULL);
}

void		*malloc(size_t size)
{
	t_region	*region_list;
	int			region_type;

	region_type = get_region_type(size);
	region_list = g_heap[region_type];
	if (region_list /* && region_list->max_contiguous_free_space >= size */)
	{
		printf("Yes REGION\n");
		region_alloc(g_heap[region_type], size);
	}
	else
	{
		printf("No REGION : %d\n", region_type);
		// FIRST REGION
		g_heap[region_type] = new_region(region_type, get_region_size(size));
		region_alloc(g_heap[region_type], size);
	}
	return (NULL);
}
