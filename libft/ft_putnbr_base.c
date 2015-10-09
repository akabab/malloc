/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 11:38:37 by slgracie          #+#    #+#             */
/*   Updated: 2015/01/10 12:00:45 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(unsigned int n, char *base)
{
	unsigned int	count;

	count = ft_strlen(base);
	if (n >= count)
		ft_putnbr_base(n / count, base);
	else
		ft_putchar(base[n % count]);
}
