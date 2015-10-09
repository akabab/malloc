/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 12:30:46 by slgracie          #+#    #+#             */
/*   Updated: 2015/02/09 14:16:20 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_push_back(t_list **alst, t_list *new)
{
	t_list	*ptr;

	if (new && alst)
	{
		if (!(*alst))
			*alst = new;
		else
		{
			ptr = *alst;
			while (ptr->next != NULL)
				ptr = ptr->next;
			ptr->next = new;
		}
	}
}
