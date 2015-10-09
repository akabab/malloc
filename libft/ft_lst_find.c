/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/10 12:39:47 by slgracie          #+#    #+#             */
/*   Updated: 2015/03/03 11:16:42 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_find(t_list *lst, void *ref)
{
	while (lst)
	{
		if (ft_memcmp(lst->content, ref, ft_strlen(ref)) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
