/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 16:04:31 by slgracie          #+#    #+#             */
/*   Updated: 2014/11/04 17:16:45 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	len_s1;

	i = 0;
	if (n == 0)
		return (s1);
	len_s1 = ft_strlen(s1);
	while (s2[i] && i < n)
	{
		s1[i + len_s1] = s2[i];
		i++;
	}
	s1[i + len_s1] = '\0';
	return (s1);
}
