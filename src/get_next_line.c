/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:19:07 by orahmoun          #+#    #+#             */
/*   Updated: 2021/11/27 15:15:45 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static void	free_null(char **p)
{
	free (*p);
	*p = NULL;
}

static char	*read_line(int fd, char *current)
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_bytes;

	read_bytes = 1;
	if (current == NULL)
		current = ft_strdup ("");
	while (!ft_strchr (current, '\n') && read_bytes)
	{
		read_bytes = read (fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free_null (&current);
			return (0);
		}
		buffer[read_bytes] = 0;
		current = ft_strjoin_free(current, buffer);
	}
	return (current);
}

static char	*return_line(char **current)
{
	char	*temp;
	char	*rest;

	if (ft_strlen(*current) && !ft_strchr (*current, '\n'))
	{
		temp = ft_strdup (*current);
		free_null (current);
		return (temp);
	}
	else if (ft_strchr (*current, '\n'))
	{
		temp = ft_substr(*current, 0, ft_strchr(*current, '\n') - *current + 1);
		rest = ft_strdup(ft_strchr(*current, '\n') + 1);
		free_null (current);
		*current = rest;
		return (temp);
	}
	free_null (current);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*current;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	current = read_line (fd, current);
	if (!current)
		return (0);
	return (return_line(&current));
}
