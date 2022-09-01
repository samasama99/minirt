/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing10.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:39:04 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/23 21:20:27 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_optional_int	parse_digit(const char *d)
{
	if (d == NULL || d[0] == '\0')
		return ((t_optional_int){.error = true});
	if (ft_strlen(d) != 1)
		return ((t_optional_int){.error = true});
	if (ft_isdigit(d[0]) != 1)
		return ((t_optional_int){.error = true});
	return ((t_optional_int){
		.value = ft_atoi(d),
		.error = false,
	});
}
