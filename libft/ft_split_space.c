/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 22:20:11 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/23 12:39:39 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static char	**free_tab(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free (tab[i++]);
	free (tab);
	return (0);
}

static char	**allocat_tab(char const *s, size_t *total)
{
	int		i;
	char	**tab;

	i = 0;
	tab = NULL;
	while (s[i])
	{
		while (is_space(s[i]))
			i++;
		while (!is_space(s[i]) && s[i])
			i++;
		if (!is_space(s[i - 1]))
			(*total)++;
	}
	tab = (char **) ft_malloc(sizeof(char *) * (*total + 1));
	if (!tab)
		return (NULL);
	tab[*total] = 0;
	return (tab);
}

static char	**allocate_string(char	**tab, char const *s, int total)
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
		while (is_space(s[i]))
			i++;
		start = i;
		while (!is_space(s[i]) && s[i])
			i++;
		if (!is_space(s[i - 1]))
		{
			tab[t] = ft_substr(s, start, i - start);
			if (tab[t] == 0)
				return (free_tab (tab, total));
			t++;
		}
	}
	return (tab);
}

char	**ft_split_space(char const *s)
{
	char	**tab;
	size_t	total;

	if (s == NULL)
		return (0);
	total = 0;
	tab = allocat_tab (s, &total);
	tab = allocate_string (tab, s, total);
	return (tab);
}
