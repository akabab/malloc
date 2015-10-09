/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 14:12:14 by slgracie          #+#    #+#             */
/*   Updated: 2014/11/06 16:46:38 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (!*s2)
		return ((char *)s1);
	while (s1[i] != '\0' && i < n)
	{
		if (s1[i] == *s2)
		{
			k = i;
			j = 0;
			while (s1[i] == s2[j] && i < n)
			{
				if (s2[j + 1] == '\0')
					return ((char *)s1 + k);
				i++;
				j++;
			}
			i = k;
		}
		i++;
	}
	return (NULL);
}
