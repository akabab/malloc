/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/05 14:05:08 by slgracie          #+#    #+#             */
/*   Updated: 2015/10/08 20:00:50 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/malloc.h"

int		init_lst_page(t_page **lst_page)
{	
/* premier appel a malloc , initialisation des pages TINY et SMALL */

	t_block	* first_b;
	void	*tiny_page = NULL;
	void	*small_page = NULL; 	
	
	tiny_page = mmap(0,TINY_SIZE, PROT_READ | PROT_WRITE, MAP_ANON| MAP_PRIVATE,-1,0);
	small_page = mmap(0,SMALL_SIZE, PROT_READ | PROT_WRITE, MAP_ANON| MAP_PRIVATE,-1,0);

	if (tiny_page == MAP_FAILED || small_page == MAP_FAILED)
		return (-1);

	first_b  = ft_lstnew_block((tiny_page + sizeof(t_page)), 0, 0); //0 libre 1 oqp
	*lst_page = ft_lstnew_page(tiny_page, TINY_SIZE, first_b);
	ft_lstadd_page(&(*lst_page), ft_lstnew_page(small_page, SMALL_SIZE, NULL));
	return (0);
}

void	*malloc(size_t size)
{
	static t_page	*lst_page = NULL;
	void			*ptr = NULL;
	(void) size;

	if (lst_page == NULL)
		init_lst_page(&lst_page);
	t_page *tmp = lst_page;
	while ((tmp) && (tmp->next != NULL || tmp->size != 0))
	{
		printf("yolo\n");
		printf("%p\n",tmp);
		tmp = tmp->next;
	}
	return ptr;

}

int main()
{
	char *ptr;
	size_t	size;

	size =13;
	ptr = (char *)malloc(size);	
}
