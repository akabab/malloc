/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 18:55:13 by slgracie          #+#    #+#             */
/*   Updated: 2014/11/12 19:36:51 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f) (char))
{
	char	*str;
	size_t	i;

	if (!(f && s))
		return (0);
	str = ft_strnew(ft_strlen(s));
	i = 0;
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = (f)(s[i]);
		i++;
	}
	return (str);
}
