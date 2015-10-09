/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 14:27:57 by slgracie          #+#    #+#             */
/*   Updated: 2014/11/09 17:40:44 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*ptr;

	ptr = (void *)ft_memalloc(n);
	ptr = ft_memcpy(ptr, src, n);
	dest = ft_memcpy(dest, ptr, n);
	free(ptr);
	return (dest);
}
