/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 14:56:11 by slgracie          #+#    #+#             */
/*   Updated: 2014/11/09 17:34:34 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	size_t	i;
	int		res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	if (!s)
		return (0);
	while (s[i] == '\n' || s[i] == '\t' || s[i] == '\r' ||
		s[i] == '\v' || s[i] == '\f' || s[i] == ' ')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = 10 * res + (s[i] - '0');
		i++;
	}
	res = res * sign;
	return (res);
}
