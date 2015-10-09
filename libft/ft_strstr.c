/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 12:31:31 by slgracie          #+#    #+#             */
/*   Updated: 2014/11/06 16:43:32 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	if (!*s2)
		return ((char *)s1);
	while (s1[i] != '\0')
	{
		if (s1[i] == *s2)
		{
			k = i;
			j = 0;
			while (s1[i] == s2[j])
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
