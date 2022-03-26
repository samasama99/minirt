/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:29:12 by orahmoun          #+#    #+#             */
/*   Updated: 2021/11/19 14:34:55 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;
	size_t	i;

	i = 0;
	tmp = (void *) malloc (size * count);
	if (!tmp)
		return (0);
	ft_bzero(tmp, count * size);
	return (tmp);
}
