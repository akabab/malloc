/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 17:20:46 by slgracie          #+#    #+#             */
/*   Updated: 2015/02/25 13:43:27 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char *dest;
	const unsigned char	*src;

	i = 0;
	dest = s1;
	src = s2;
	if (src[i] && dest[i])
	{
		if (n == 0 || s1 == s2)
			return (0);
		while (i < n && dest[i] && src[i])
		{
			if (dest[i] != src[i] || dest[i] == '\0' || src[i] == '\0')
				return ((unsigned char)dest[i] - (unsigned char)src[i]);
			i++;
		}
	}
	return (0);
}
