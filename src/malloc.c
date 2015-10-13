#include "malloc.h"

t_region		*g_heap[3];

void		show_alloc_mem(void);

void		free(void *ptr);
void		*realloc(void *ptr, size_t size);

int			get_region_type(size_t size)
{
	if (size < TINY_BLOCK_MAX_SIZE)
		return TINY;
	if (size < SMALL_BLOCK_MAX_SIZE)
		return SMALL;
	return LARGE;
}

size_t		get_region_size(t_region_type type)
{
	size_t		region_size;
	size_t		block_size;

	if (type == TINY)
		block_size = TINY_BLOCK_MAX_SIZE;
	else if (type == SMALL)
		block_size = SMALL_BLOCK_MAX_SIZE;
	// else if (type == LARGE)
		// block_size = LARGE_BLOCK_MAX_SIZE;
	else
		return 0;
	region_size = (block_size + BLOCK_META_SIZE) * 100;
	printf("region_size: %zu\n", region_size);
	return region_size;
}

void		malloc_init(void)
{
	g_heap[0] = NULL;
	g_heap[1] = NULL;
	g_heap[2] = NULL;
}

t_block_meta	*new_block(size_t size)
{
	t_block_meta	*block;

	block->size = size;
	block->prev = NULL;
	block->next = NULL;
	block->free = TRUE;
	return block;
}

t_region	*new_region(t_region_type type)
{
	int			prot;
	int			flags;
	size_t		size;
	t_region	*region;

	prot = PROT_READ | PROT_WRITE;
	flags = MAP_ANON | MAP_PRIVATE;
	if ((size = get_region_size(type)) == 0)
		return NULL;
	region = mmap(0, size, prot, flags, -1, 0);
	if (region == MAP_FAILED)
	{
		/* errno contains error */
		return NULL;
	}
	region->type = type;
	region->size = size;
	region->next = NULL;
	region->block_list = (t_block_meta *)(region + sizeof(t_region));
	return region;
}

void		*malloc(size_t size)
{

	malloc_init();

	// size check
	int		region_type;

	region_type = get_region_type(size);

	// check for free space
	t_region	*region_list;
	region_list = g_heap[region_type];
	if (region_list != NULL /* && region_list->max_contiguous_free_space >= size */)
	{
		// add block
	}
	else
	{
		// add region
		new_region(region_type);
			// add block
	}

	// allocate

	return NULL;
}
