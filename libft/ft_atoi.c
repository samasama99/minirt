/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:44:44 by orahmoun          #+#    #+#             */
/*   Updated: 2021/11/19 14:34:17 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static unsigned int	ft_isspace(char sp)
{
	if ((sp >= 9 && sp <= 13) || sp == 32)
		return (1);
	return (0);
}

static long long	ft_calclenght(const char *str)
{
	unsigned long	x;
	int				i;

	i = 0;
	x = 1;
	while (str[i] >= 48 && str[i] <= 57)
	{	
		x = x * 10;
		i++;
	}
	return (x / 10);
}

int	ft_atoi(const char *str)
{
	int					s;
	unsigned int		i;
	unsigned long long	t;
	unsigned long long	x;

	s = 1;
	i = 0;
	t = 0;
	x = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		s = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	x = ft_calclenght(&str[i]);
	while (str[i] >= 48 && str[i] <= 57)
	{
		t = ((str[i++] - 48) * x) + t;
		x = x / 10;
	}
	return (s * t);
}
