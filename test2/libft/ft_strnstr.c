/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:45:17 by orahmoun          #+#    #+#             */
/*   Updated: 2021/11/19 14:41:50 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n;
	size_t	i;
	size_t	len2;

	len2 = len;
	i = 0;
	n = ft_strlen (needle);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len2)
	{
		if (ft_strncmp(&haystack[i], needle, n) == 0 && n <= len)
			return ((char *)(haystack + i));
		else
			i++;
		len--;
	}
	return (NULL);
}
