/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 19:41:54 by slgracie          #+#    #+#             */
/*   Updated: 2014/11/12 20:46:32 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	if (!f || !s)
		return (0);
	str = ft_strnew(ft_strlen(s));
	i = 0;
	while (s[i])
	{
		str[i] = (f)(i, s[i]);
		i++;
	}
	return (str);
}
