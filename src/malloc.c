#include "malloc.h"

t_region		*g_heap[3] = {NULL};
int	g_test = 0;

void		ft_putchar(const char c)
{
	write(1, &c, 1);
}

void		ft_putstr(const char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

void		ft_putchar_fd(const char c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putstr_fd(const char *str, int fd)
{
	while (*str)
	{
		ft_putchar_fd(*str, fd);
		str++;
	}
}

void		ft_putendl_fd(const char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_perror(const char *msg)
{
	extern const int			errno;
	extern const char	* const sys_errlist[];

	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(sys_errlist[errno], 2);
}

void		show_region_mem(t_region *region_list, char *type_str)
{
	t_region	*cur_region;
	t_block		*cur_block;
	size_t		total_regions;
	size_t		total_bytes;

	total_bytes = 0;
	total_regions = 0;
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
			printf(" %p (%p) - %zu bytes\n", cur_block, cur_block->data, cur_block->size);
			printf("===============\n"C(NO));
			if (!cur_block->is_free)
				total_bytes += cur_block->size;
			cur_block = cur_block->next;
		}
		printf(CB(BLUE)"...> %p <....................\n"C(NO), cur_region->data + REGION_SIZE + cur_region->size);
		total_regions++;
		cur_region = cur_region->next;
	}
	printf(C(YELLOW)"%s"C(NO)" - %zu bytes (%zu regions)\n", type_str, total_bytes, total_regions); // ft_
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

t_block		*get_block(void *ptr)
{
	char	*tmp;

	tmp = ptr;
	ptr = tmp - BLOCK_SIZE;
	return (ptr);
}

t_bool		is_valid_addr(void *ptr)
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
				// printf("IS VALID ADDR: %d\n", b->ptr == ptr);
				return (b->ptr == ptr);
			}
			cur_r = cur_r->next;
		}
		i++;
	}
	// printf("IS NOT VALID ADDR\n");
	return (FALSE);
}

void		free(void *ptr)
{
	t_block		*block;

	if (is_valid_addr(ptr))
	{
		block = get_block(ptr);
		printf("block %p (%p) - %zu bytes\n", block, block->data, block->size);
		block->is_free = TRUE;
	}
	else
	{
		printf("malloc: *** error for object %p: pointer being freed was not allocated\n", ptr);
		exit(-1);
	}
	// if (munmap(addr, len) == -1)
	// {
	// 	ft_perror("munmap failed");
	// 	return ;
	// }
}

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

t_region	*get_last_region(t_region *region)
{
	t_region	*cur_region;

	cur_region = region;
	while (cur_region && cur_region->next)
		cur_region = cur_region->next;
	return (cur_region);
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

void		split_block(t_block *b, size_t size)
{
	t_block		*new_b;

	new_b = new_block(b->data + size, b->size - size - BLOCK_SIZE);
	new_b->next = b->next;
	b->size = size;
	b->next = new_b;
}

t_region	*new_region(t_region_size size)
{
	t_region	*region;
	int			prot;
	int			flags;

	prot = PROT_READ | PROT_WRITE;
	flags = MAP_ANON | MAP_PRIVATE;
	region = mmap(0, size, prot, flags, -1, 0);
	if (region == MAP_FAILED)
	{
		ft_perror(NULL);
		return (NULL);
	}
	region->size = size - REGION_SIZE;
	region->next = NULL;
	region->block_list = NULL;
	printf("NEW REGION : [%p-%p] - %zu bytes\n", region, region->data + size, region->size);
	return (region);
}

t_block		*extend_region(t_region **region, size_t size)
{
	t_region	*new_r;
	t_region	*last;
	t_block		*new_b;

	last = get_last_region(*region);
	new_r = new_region(get_region_size(size));
	if (!new_r)
		return (NULL);
	// Init first block of region
	new_b = new_block(new_r->data + REGION_SIZE, 0);
	if (get_region_type(size) == LARGE)
		new_b->size = size;
	else
	{
		new_b->size = new_r->size - BLOCK_SIZE;
		// alloc new block with size
		if (new_b->size > size && (new_b->size - size) >= BLOCK_SIZE)
			split_block(new_b, size);
	}
	new_b->is_free = FALSE;
	new_r->block_list = new_b;
	if (last)
		last->next = new_r;
	else
		*region = new_r;
	return (new_b);
}

void		*region_alloc(t_region *region, size_t size)
{
	t_block *b = get_free_block(region, size);
	if (b)
	{
		// printf("found free block: %p (%zu)\n", b, b->size);
		// SPLIT
		if ((b->size - size) >= BLOCK_SIZE)
		{
			// printf("SPLIT\n");
			split_block(b, size);
		}
		else
		{
			printf("SPLIT: not enough space for new block so allocate whole block\n");
		}
		b->is_free = FALSE;
		return (b);
	}
	else
	{
		printf("no free block -> extend_region\n");
		b = extend_region(&region, size);
		return (b);
	}
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
		printf("FIRST REGION : %d\n", region_type);
		block = extend_region(&g_heap[region_type], size);
		if (!block)
			return (NULL);
	}
	return (block->data);
}
