/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 22:20:11 by orahmoun          #+#    #+#             */
/*   Updated: 2021/11/19 14:40:13 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	**free_tab(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free (tab[i++]);
	free (tab);
	return (0);
}

static	char	**allocat_tab(char const *s, char c, int *total)
{
	int		i;
	char	**tab;

	i = 0;
	tab = NULL;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
			i++;
		if (s[i - 1] != c)
			(*total)++;
	}
	tab = (char **) malloc(sizeof(char *) * (*total + 1));
	if (!tab)
		return (0);
	tab[*total] = 0;
	return (tab);
}

static char	**allocate_string(char	**tab, char const *s, char c, int total)
{	
	int		i;
	int		t;
	int		start;

	if (!tab)
		return (0);
	t = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (s[i - 1] != c)
		{
			tab[t] = ft_substr(s, start, i - start);
			if (tab[t] == 0)
				return (free_tab (tab, total));
			t++;
		}
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		total;

	if (s == NULL)
		return (0);
	total = 0;
	tab = allocat_tab (s, c, &total);
	tab = allocate_string (tab, s, c, total);
	return (tab);
}
