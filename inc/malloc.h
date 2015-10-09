/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 15:10:04 by slgracie          #+#    #+#             */
/*   Updated: 2015/10/09 17:43:21 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include <sys/mman.h>
# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"

# define TINY_SIZE (4 * getpagesize())
# define TINY_MAX (128)

# define SMALL_SIZE (26 * getpagesize())
# define SMALL_MAX (1024)

typedef struct 	s_block{
	int 		size;
	struct 		s_block *prev;
	struct 		s_block *next;
	int 		free;
}				t_block;

typedef struct 	s_page{
	int 		size;
	struct 		s_page *prev;
	struct 		s_page *next;
	t_block* 	first_block;
}				t_page;


t_block	*ft_lstnew_block(t_block *maillons, int size, int free);
void	ft_lstadd_block(t_block **alst, t_block *new);
void	ft_lstdelone_block(t_block **alst, t_block **ptr);
void	ft_to_null_block(t_block *list);

t_page	*ft_lstnew_page(t_page *maillons, int size, t_block *first);
void	ft_lstadd_page(t_page **alst, t_page *new);
void	ft_lstdelone_page(t_page **alst, t_page **ptr);
void	ft_to_null_page(t_page *list);

#endif
