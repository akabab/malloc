/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 14:10:20 by slgracie          #+#    #+#             */
/*   Updated: 2014/11/12 18:51:44 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countword(const char *s, char c)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	if (s[0] != c && s[i])
		k++;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (!(s[i + 1] == c || s[i + 1] == '\0'))
				k++;
		}
		i++;
	}
	return (k);
}

static char		**ft_addword(char **tab, char const *s, char c)
{
	size_t	j;
	size_t	l;
	size_t	i;

	i = 0;
	l = 0;
	while (l < ft_countword(s, c))
	{
		if (s[i] != c && s[i])
		{
			j = i + 1;
			while (s[j] != c)
			{
				if (s[j] == '\0')
					break ;
				j++;
			}
			if (!(tab[l] = ft_strsub(s, i, (j - i))))
				return (NULL);
			i = j;
			l++;
		}
		i++;
	}
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	k;
	char	**tab;

	if (!s)
		return (NULL);
	k = ft_countword(s, c);
	if (!(tab = (char **)ft_memalloc(sizeof(char *) * (k + 1))))
		return (NULL);
	if (k)
		ft_addword(tab, s, c);
	return (tab);
}
