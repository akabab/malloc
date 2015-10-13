#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <stdio.h>

# define TINY_QUANTUM			32
# define TINY_BLOCK_MAX_SIZE	992
# define TINY_REGION_SIZE		25 * 4096
# define TINY_REGION_PAGES		25

// #if (TINY_REGION_SIZE <= (TINY_BLOCK_MAX_SIZE + 32) * 100)
// # error "NO NO NO"
// #endif

# define SMALL_QUANTUM			1024
# define SMALL_BLOCK_MAX_SIZE	15360
# define SMALL_REGION_SIZE		400 * 4096
# define SMALL_REGION_PAGES		400

# define LARGE_QUANTUM			4096

# define PAGE_SIZE				(getpagesize())

typedef enum		e_region_type
{
	TINY,
	SMALL,
	LARGE
}					t_region_type;

typedef enum		e_bool
{
	FALSE,
	TRUE
}					t_bool;

typedef struct s_block	t_block;
struct s_block
{
	size_t				size;
	t_block				*prev;
	t_block				*next;
	t_bool				is_free;
};

typedef struct s_region		t_region;
struct s_region
{
	t_region_type		type;
	size_t				size;
	t_region			*next;
	//size_t			max_contiguous_free_space;
	t_block				*block_list;
};

# define REGION_META_SIZE		(sizeof(t_region))
# define BLOCK_META_SIZE		(sizeof(t_block))

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

void	show_alloc_mem(void);

#endif
