/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/05 14:05:08 by slgracie          #+#    #+#             */
/*   Updated: 2015/10/09 17:43:17 by slgracie         ###   ########.fr       */
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

int 	check_size(size_t size)
{
	if ((int)size <= TINY_SIZE)
		return (TINY_SIZE);
	else if ((int)size <= SMALL_SIZE)
		return (SMALL_SIZE);
	else
		return (size);
}

void	*alloc_in_page(t_page *page, size_t size)
{
	t_block *tmp = page->first_block;
	t_block *newblock = NULL;

	while ((tmp) && (tmp->next != NULL || tmp->size != 0))
	{
		tmp = tmp->next;
	}
	if ((newblock = ft_lstnew_block(tmp + tmp->size, size, 1)) != NULL)
		return (newblock + sizeof(t_block));
	else
	{
		printf("alloc in page foireux\n");
		return (NULL);
	}
}

void	*alloc_in_tiny(t_page *lst_page, size_t size)
{

	printf("alloc_in tiny\n");
	t_page	*tmp = lst_page;
	void	*ret_alloc = NULL;

	while ((tmp) && (tmp->next != NULL || tmp->size != 0))
	{
		if (tmp->size == TINY_SIZE)
		{
			if ((ret_alloc = alloc_in_page(tmp, size))== NULL)
			{
				printf("alloc in tiny foireux\n");
				return (NULL);
			}
		}
		tmp = tmp->next;
	}
	printf("retalloc 1 = %p\n", ret_alloc);
	return (ret_alloc);

}

void	*alloc_type(int type, t_page *lst_page, size_t size)
{
	void	*ret_alloc = NULL;

	printf("alloc_type\n");
	if (type == TINY_SIZE)
		ret_alloc = alloc_in_tiny(lst_page, size);
/*	else if(type == SMALL_SIZE)
		ret_alloc = alloc_in_small(lst_page, size);
	else
		ret_alloc = alloc_large(lst_page, size);*/
	return (ret_alloc);
}

void	*malloc(size_t size)
{
	printf("a\n");
	static t_page	*lst_page = NULL;
	void			*ptr = NULL;
	(void) size;


	if (lst_page == NULL)
		init_lst_page(&lst_page);
	/*check size*/
	int type;
	type = check_size(size);
	printf("type = %d\n", type);
	/*allocation en fonction du type*/
	ptr = alloc_type(type, lst_page, size);
	return ptr;

}

int main()
{
	char *ptr;
	size_t	size;

	size =13;
	ptr = (char*)malloc(size);
	char *str ="eeeeeeeeeeeeeee";
	ptr = ft_strcpy(ptr, str); 
	printf("ptr[0] = %s\n", ptr);
	return 0;
}

/* A Faire 

   -fonction calcul de la place restante sur une page
   	(taille de la page - (sizeof du nombre de block + size de tous les  blocks);
	==> pour ne pouvoir allouer que 100 malloc sur chaque page(tiny et small);
