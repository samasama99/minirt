/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:30:08 by orahmoun          #+#    #+#             */
/*   Updated: 2021/11/19 13:30:07 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp;
	unsigned char	byte;

	byte = c;
	temp = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (temp[i] == byte)
			return ((void *)&s[i]);
		i++;
	}
	return (0);
}
