/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 15:41:12 by slgracie          #+#    #+#             */
/*   Updated: 2014/11/10 17:30:02 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del) (void *, size_t))
{
	t_list	*lst;
	t_list	*lstnext;

	if (alst)
	{
		lst = *alst;
		while (lst)
		{
			lstnext = lst->next;
			ft_lstdelone(&lst, del);
			lst = lstnext;
		}
		*alst = NULL;
	}
}
