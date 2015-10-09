/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 12:42:22 by slgracie          #+#    #+#             */
/*   Updated: 2014/12/01 16:07:12 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUF_SIZE 8
# include <string.h>

typedef struct	s_gnl_buf
{
	size_t		size;
	char		tab[BUF_SIZE];
}				t_gnl_buf;

int				get_next_line(int const fd, char **line);
#endif
