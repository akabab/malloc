/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 17:39:07 by slgracie          #+#    #+#             */
/*   Updated: 2015/03/03 11:17:02 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*tab;

	if (size > 0)
	{
		if (!(tab = (void *)malloc(size)))
			return (NULL);
		ft_bzero(tab, size);
		return (tab);
	}
	return (NULL);
}
