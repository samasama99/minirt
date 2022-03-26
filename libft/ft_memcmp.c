/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:26:37 by orahmoun          #+#    #+#             */
/*   Updated: 2021/11/19 14:38:04 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*bf1;
	unsigned char	*bf2;

	if (!s1 && !s2)
		return (0);
	if (n == 0)
		return (0);
	bf1 = (unsigned char *)s1;
	bf2 = (unsigned char *)s2;
	i = 0;
	while ((bf1[i] == bf2[i]) && i < n - 1)
		i++;
	return (bf1[i] - bf2[i]);
}
