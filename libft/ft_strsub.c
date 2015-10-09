/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 14:32:28 by slgracie          #+#    #+#             */
/*   Updated: 2014/11/12 20:10:16 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s1, unsigned int start, size_t len)
{
	char			*str_new;
	unsigned int	i;

	if (!(s1))
		return (NULL);
	i = 0;
	str_new = ft_strnew(len);
	if (!str_new)
		return (NULL);
	while (i < len)
	{
		str_new[i] = s1[start + i];
		i++;
	}
	return (str_new);
}
