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
			return (NULL);
		}
		buffer[read_bytes] = 0;
		current = ft_strjoin(current, buffer);
	}
	return (current);
}

static char	*return_line(char **current)
{
	char	*temp;
	char	*rest;

	if (ft_strlen(*current) && !ft_strchr (*current, '\n'))
	{
		return (ft_strdup (*current));
	}
	else if (ft_strchr (*current, '\n'))
	{
		temp = ft_substr(*current, 0, ft_strchr(*current, '\n') - *current + 1);
		rest = ft_strdup(ft_strchr(*current, '\n') + 1);
		*current = rest;
		return (temp);
	}
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

char *read_file(int fd)
{
  char *total;
  char buffer[2];
  int b;

  total = ft_strdup("\0");
  while (1)
  {
    b = read(fd, buffer, 1);
    if (b <= 0)
        break;
    buffer[1] = '\0';
    total = ft_strjoin(total, buffer);
  }
  if (total && total[0] == '\0')
    return NULL;
  return total;
}
