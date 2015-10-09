/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 17:36:52 by slgracie          #+#    #+#             */
/*   Updated: 2014/11/05 14:00:19 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strlcat(char *s1, const char *s2, size_t size)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s1);
	if (i >= size)
		return (size + ft_strlen(s2));
	j = 0;
	while (i + j < size - 1 && s2[j])
	{
		s1[i + j] = s2[j];
		j++;
	}
	s1[i + j] = '\0';
	return (i + ft_strlen(s2));
}
