#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

# define PAGE_SIZE				(getpagesize())

# define TINY_QUANTUM			32
# define TINY_BLOCK_MAX_SIZE	992
# define TINY_REGION_SIZE		25 * PAGE_SIZE
# define TINY_REGION_PAGES		25

# define SMALL_QUANTUM			1024
# define SMALL_BLOCK_MAX_SIZE	15360
# define SMALL_REGION_SIZE		400 * PAGE_SIZE
# define SMALL_REGION_PAGES		400

# define LARGE_QUANTUM			PAGE_SIZE

typedef enum				e_bool
{
	FALSE,
	TRUE
}							t_bool;

/*
** BLOCK
*/
typedef size_t				t_block_size;

typedef struct s_block		t_block;
struct						s_block
{
	t_block_size			size;
	t_block					*prev;
	t_block					*next;
	t_bool					is_free;
	void					*ptr;
	char					data[1];
};

# define BLOCK_SIZE			5*8

/*
** REGION
*/
typedef enum				e_region_type
{
	TINY,
	SMALL,
	LARGE
}							t_region_type;

typedef size_t				t_region_size;

typedef struct s_region		t_region;
struct						s_region
{
	t_region_size			size;
	t_region_type			type;
	t_region				*prev;
	t_region				*next;
	t_block					*block_list;
	char					data[1];
};

# define REGION_SIZE		4*8

/*
**		malloc.c
*/
void						*malloc_exec(size_t size);
void						*malloc(size_t size);

/*
**		free.c
*/
void						free_exec(void *ptr);
void						free(void *ptr);

/*
**		realloc.c
*/
void						*realloc(void *ptr, size_t size);

/*
**		show_alloc.c
*/
void						show_alloc_mem(void);
void						show_alloc_mem_ex(void);

/*
**		ft_perror.c
*/
void						ft_perror(const char *msg);
void						malloc_err(const char *msg, void *ptr);

/*
**		ft_puts.c
*/
void						ft_putchar(const char c);
void						ft_putstr(const char *str);
void						ft_putchar_fd(const char c, int fd);
void						ft_putstr_fd(const char *str, int fd);
void						ft_putendl_fd(const char *s, int fd);

/*
**		ft_puts_plus.c
*/
void						ft_putnbr(int n);
size_t						ft_strlen(char *s);

/*
**		ft_printf.c
*/
int							ft_printf(const char *format, ...);

/*
**		region_utils.c
*/
int							get_region_type(size_t size);
size_t						get_region_size(size_t size);
t_region					*get_last_region(t_region *region);
t_block						*extend_region(t_region **region, size_t size);
t_region					*new_region(t_region_type type, t_region_size s);

/*
**		region_utils_plus.c
*/
void						free_region(t_region *r);
t_block						*get_free_block(t_region *region, size_t size);
t_region					*get_valid_region(void *ptr);
void						*region_alloc(t_region *region, size_t size);

/*
**		block_utils.c
*/
t_block						*get_block(void *ptr);
void						copy_data(t_block *src, t_block *dst);
t_block						*fusion_block(t_block *b);
void						split_block(t_block *b, size_t size);
t_block						*new_block(void *at, size_t size);

/*
**		COLOR
*/
# define RED				"31"
# define GREEN				"32"
# define YELLOW				"33"
# define BLUE				"34"
# define PINK				"35"
# define GRBL				"36"
# define GREY				"37"
# define NO					"0"
# define C(X)				"\033["X"m"
# define CC(X)				"\033[3"X"m"
# define CB(X)				"\x1B[48;1;"X"m"
# define CBNO				"\x1B[0m"

#endif
