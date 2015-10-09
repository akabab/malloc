/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 16:49:42 by slgracie          #+#    #+#             */
/*   Updated: 2014/11/12 19:44:58 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	const unsigned char		*s1;
	unsigned char			c1;

	i = 0;
	s1 = s;
	c1 = c;
	while (i < n)
	{
		if (s1[i] == (c1))
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}
