/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 13:23:20 by slgracie          #+#    #+#             */
/*   Updated: 2014/11/06 16:28:07 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*str;
	unsigned int	i;

	i = 0;
	str = NULL;
	while (s[i])
	{
		if ((char)c == s[i])
			str = (char *)s + i;
		i++;
	}
	if ((char)c == s[i])
		str = (char *)s + i;
	return (str);
}
