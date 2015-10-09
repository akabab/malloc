/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 11:54:08 by slgracie          #+#    #+#             */
/*   Updated: 2015/01/10 11:57:18 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_range_tab(int *tab, int size)
{
	int	i;
	int	j;
	int temp;

	i = 0;
	j = 0;
	temp = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			if (tab[i] > tab[i + 1])
			{
				temp = tab[i + 1];
				tab[i + 1] = tab[i];
				tab[i] = temp;
			}
			i++;
		}
		j++;
	}
}
