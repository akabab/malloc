/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 14:05:02 by slgracie          #+#    #+#             */
/*   Updated: 2015/05/07 15:10:38 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <unistd.h>

static t_gnl_buf	*alloc_tab(int fd, t_gnl_buf *save[256])
{
	if (save[fd] == NULL)
	{
		if (!(save[fd] = ft_memalloc(sizeof(t_gnl_buf))))
			return (NULL);
	}
	return (save[fd]);
}

static int			load_save(t_gnl_buf *save[256], char buf[]
						, int *total_size, int fd)
{
	char *ptr;

	*total_size = save[fd]->size + 1;
	ft_memcpy(buf, save[fd]->tab, (save[fd])->size);
	if ((ptr = ft_memchr(save[fd]->tab, '\n', save[fd]->size)))
	{
		*total_size = (int)(ptr - save[fd]->tab) + 1;
		save[fd]->size = save[fd]->size - *total_size;
		ft_memcpy(save[fd]->tab, ptr + 1, save[fd]->size);
		return (1);
	}
	save[fd]->size = 0;
	return (0);
}

static int			read_gnl(char **line, int fd, t_gnl_buf *save[256]
						, int total_size)
{
	char	buf[BUF_SIZE];
	int		ret;
	char	*ptr;

	ptr = NULL;
	while ((ret = read(fd, buf, BUF_SIZE)) > 0)
	{
		if ((ptr = ft_memchr(buf, '\n', ret)))
		{
			save[fd]->size = ret - (int)(ptr - buf) - 1;
			ft_memcpy(save[fd]->tab, (ptr + 1), save[fd]->size);
			ret = (int)(ptr - buf);
		}
		if (!ft_realloc((void **)line, total_size - 1, (total_size + ret)))
			return (-1);
		ft_memcpy(*line + total_size - 1, buf, ret);
		total_size = total_size + ret;
		if (ptr)
			break ;
	}
	if (ret == -1)
		return (-1);
	return (ptr ? 1 : 0);
}

static int			check_return_value(int const fd, char **line
						, t_gnl_buf **save)
{
	char					buf[BUF_SIZE];
	int						ret;
	int						total_size;

	ret = 0;
	if (line == NULL || fd < 0 || fd > 255)
		return (-1);
	ret = load_save(save, buf, &total_size, fd);
	if (!(*line = ft_memalloc(total_size)))
		return (-1);
	ft_memcpy(*line, buf, *line ? total_size - 1 : 0);
	if (ret)
		return (1);
	if ((ret = read_gnl(line, fd, save, total_size)) == -1)
		return (-1);
	if (save[fd]->size == 0 && ret == 0)
		return (0);
	return (1);
}

int					get_next_line(int const fd, char **line)
{
	static t_gnl_buf	*save[256];
	int					k;

	alloc_tab(fd, save);
	k = check_return_value(fd, line, save);
	if (k == -1)
	{
		ft_memdel((void **)&save[fd]);
		return (-1);
	}
	else if (k == 0)
	{
		ft_memdel((void **)&save[fd]);
		return (0);
	}
	else
		return (1);
}
