/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:10:36 by orahmoun          #+#    #+#             */
/*   Updated: 2021/11/19 14:38:41 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	size_t	j;
	char	*bf1;
	char	*bf2;

	if (!dst && !src)
		return (0);
	bf1 = dst;
	bf2 = (char *)src;
	i = 0;
	j = len;
	if (dst >= src)
		while (j--)
			bf1[j] = bf2[j];
	else
	{
		while (i < len)
		{
			bf1[i] = bf2[i];
			i++;
		}
	}
	return (dst);
}
