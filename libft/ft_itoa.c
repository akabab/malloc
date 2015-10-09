/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 13:19:47 by slgracie          #+#    #+#             */
/*   Updated: 2014/11/09 17:41:37 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len_n(int n)
{
	if (n < 0)
		return (1 + ft_len_n(-n));
	if (n < 10)
		return (1);
	else
		return (1 + ft_len_n(n / 10));
}

char		*ft_itoa(int n)
{
	int		i;
	int		len;
	int		sign;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_len_n(n);
	i = len - 1;
	sign = n < 0;
	n = sign ? -n : n;
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	while (i >= sign)
	{
		str[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}
