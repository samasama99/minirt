/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:36:56 by orahmoun          #+#    #+#             */
/*   Updated: 2021/11/19 14:41:12 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	s;
	size_t	d;
	size_t	i;

	i = 0;
	s = ft_strlen (src);
	d = ft_strlen (dst);
	if (dstsize < d)
	{
		s = s + dstsize;
	}
	else
	{
		s = s + d;
		while ((src[i] != '\0') && (d + 1 < dstsize))
		{
			dst[d] = src[i];
			d++;
			i++;
		}
		dst[d] = '\0';
	}
	return (s);
}
