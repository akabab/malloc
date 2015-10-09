/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 13:58:36 by slgracie          #+#    #+#             */
/*   Updated: 2014/11/19 19:37:47 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdlib.h>

void	*ft_realloc(void **p, size_t size, size_t newsize)
{
	void	*p_new;

	if (!(p_new = ft_memalloc(newsize)))
	{
		ft_memdel
			(p);
		return (NULL);
	}
	ft_memcpy(p_new, *p, size);
	free(*p);
	*p = p_new;
	return (p_new);
}
