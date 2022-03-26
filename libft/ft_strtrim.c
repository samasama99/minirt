/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:45:08 by orahmoun          #+#    #+#             */
/*   Updated: 2022/02/15 18:06:51 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_charexist(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	char	*temp;
	int		i;
	int		j;

	if (!s || !set)
		return (0);
	i = 0;
	j = ft_strlen(s) - 1;
	while (i < j && ft_charexist (s[i], set))
		i++;
	if (i == j && !ft_charexist (s[i], set))
		return ((char *)s);
	if (i >= j)
	{	
		temp = (char *)malloc(1);
		temp[0] = '\0';
		return (temp);
	}
	while (j > i && ft_charexist (s[j], set))
		j--;
	temp = ft_substr (s, i, j - i + 1);
	if (!temp)
		return (0);
	return (temp);
}
