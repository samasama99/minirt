/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:11:07 by orahmoun          #+#    #+#             */
/*   Updated: 2021/11/19 14:38:22 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*bf1;
	unsigned char	*bf2;
	size_t			i;

	i = 0;
	bf1 = dst;
	bf2 = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		bf1[i] = bf2[i];
		i++;
	}
	return (dst);
}
