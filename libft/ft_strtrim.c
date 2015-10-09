/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slgracie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 17:14:06 by slgracie          #+#    #+#             */
/*   Updated: 2014/11/12 20:19:18 by slgracie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!s)
		return (NULL);
	j = ft_strlen(s) - 1;
	if (s[i] == '\0')
		return (ft_strdup(""));
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && (s[i] != '\0'))
		i++;
	if (s[i] == '\0')
		return (ft_strdup(""));
	while ((s[j] == ' ' || s[j] == '\n' || s[j] == '\t'))
		j--;
	if (i == 0 && j == ft_strlen(s))
		return (ft_strdup(s));
	return (ft_strsub(s, i, (j - i) + 1));
}
