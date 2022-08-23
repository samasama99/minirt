/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:01:57 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/23 12:36:02 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdlib.h>

void	safe_close(int fd)
{
	if (fd != 0 && fd != 1 && fd != -1)
		close (fd);
}

void	panic(bool con, const char *msg, const char *func)
{
	if (con == true)
	{
		printf ("\033[31mPanic [%s] : %s\033[0m\n", func, msg);
		exit (1);
	}
}

bool	is_equal_str(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len != s2_len)
		return (false);
	return (ft_strncmp(s1, s2, s1_len) == 0);
}

float	clamp(float n, float min, float max)
{
	if (n > max)
		n = 1;
	if (n < min)
		n = 0;
	return (n);
}
