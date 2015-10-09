/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achirouz <achirouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 16:20:29 by achirouz          #+#    #+#             */
/*   Updated: 2015/10/08 19:42:34 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/malloc.h"


/* list block function */

void	ft_to_null_block(t_block *list)
{
	list->next = NULL;
	list->prev = NULL;
}

t_block	*ft_lstnew_block(t_block *maillons, int size, int free)
{
	t_block	*newlist;

/*	if (!(newlist = malloc(sizeof(*newlist))))
		return (NULL);*/
	newlist = maillons;
	if (!size)
		ft_to_null_block(newlist);
	else
	{
		newlist->next = NULL;
		newlist->prev = NULL;
		newlist->size = size;
		newlist->free = free;
	}
	return (newlist);
}

void	ft_lstadd_block(t_block **alst, t_block *new)
{
	t_block	*cur;

	if (!alst)
		return ;
	if (!(*alst))
	{
		*alst = new;
		return ;
	}
	cur = *alst;
	while (cur->next)
		cur = cur->next;
	new->prev = cur;
	cur->next = new;
}

void	ft_lstdelone_block(t_block **alst, t_block **ptr)
{
	t_block	*ptr1;
	t_block	*ptr2;

	ptr2 = (*alst)->next;
	ptr1 = (*alst);
	if (ptr1 == *ptr)
	{
		(*alst) = ptr1->next;
		return ;
	}
	while (ptr1->next)
	{
		if (ptr2 == *ptr)
		{
			ptr1->next = ptr2->next;
			break ;
		}
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}
}

/* list page function */

void	ft_to_null_page(t_page *list)
{
	list->next = NULL;
	list->prev = NULL;
}

t_page	*ft_lstnew_page(t_page *maillons, int size, t_block *first_block)
{
	t_page	*newlist;

/*	if (!(newlist = malloc(sizeof(*newlist))))
		return (NULL);*/
	newlist = maillons;
	if (!size)
		ft_to_null_page(newlist);
	else
	{
		newlist->next = NULL;
		newlist->prev = NULL;
		newlist->size = size;
		newlist->first_block = first_block;
	}
	return (newlist);
}

void	ft_lstadd_page(t_page **alst, t_page *new)
{
	t_page	*cur;

	if (!alst)
		return ;
	if (!(*alst))
	{
		*alst = new;
		return ;
	}
	cur = *alst;
	while (cur->next)
		cur = cur->next;
	new->prev = cur;
	cur->next = new;
}

void	ft_lstdelone_page(t_page **alst, t_page **ptr)
{
	t_page	*ptr1;
	t_page	*ptr2;

	ptr2 = (*alst)->next;
	ptr1 = (*alst);
	if (ptr1 == *ptr)
	{
		(*alst) = ptr1->next;
		return ;
	}
	while (ptr1->next)
	{
		if (ptr2 == *ptr)
		{
			ptr1->next = ptr2->next;
			break ;
		}
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}
}
