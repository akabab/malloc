#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define PAGE_SIZE				(getpagesize())

# define TINY_QUANTUM			32
# define TINY_BLOCK_MAX_SIZE	992
# define TINY_REGION_SIZE		25 * PAGE_SIZE
# define TINY_REGION_PAGES		25

// #if (TINY_REGION_SIZE <= (TINY_BLOCK_MAX_SIZE + 32) * 100)
// # error "NO NO NO"
// #endif

# define SMALL_QUANTUM			1024
# define SMALL_BLOCK_MAX_SIZE	15360
# define SMALL_REGION_SIZE		400 * PAGE_SIZE
# define SMALL_REGION_PAGES		400

# define LARGE_QUANTUM			PAGE_SIZE


typedef enum		e_bool
{
	FALSE,
	TRUE
}					t_bool;

/*
** BLOCK
*/
typedef size_t		t_block_size;

typedef struct s_block	t_block;
struct s_block
{
	t_block_size		size;
	t_block				*prev;
	t_block				*next;
	t_bool				is_free;
	void				*ptr;
	char				data[1];
};

# define BLOCK_SIZE		5*8

/*
** REGION
*/
typedef enum		e_region_type
{
	TINY,
	SMALL,
	LARGE
}					t_region_type;

typedef size_t		t_region_size;

typedef struct s_region		t_region;
struct s_region
{
	t_region_size		size;
	t_region			*next;
	t_block				*block_list;
	char				data[1];
};

# define REGION_SIZE	3*8

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

void	show_alloc_mem(void);

/*
**		COLOR
*/
# define RED			"31"
# define GREEN			"32"
# define YELLOW			"33"
# define BLUE			"34"
# define PINK			"35"
# define GRBL			"36"
# define GREY			"37"
# define NO				"0"
# define C(X)			"\033["X"m"
# define CC(X)			"\033[3"X"m"
# define CB(X)			"\x1B[48;1;"X"m"
# define CBNO			"\x1B[0m"

#endif
