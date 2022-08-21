/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:44:25 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/21 14:44:37 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_optional_int	parse_int(const char *target)
{
	int	sign;

	sign = 1;
	if (target == NULL)
		return ((t_optional_int){.error = true});
	if (ft_isnumber(target + (target[0] == '-')) == false)
		return ((t_optional_int){.error = true});
	if (target[0] == '-')
		sign = -1;
	return ((t_optional_int){
		.value = ft_atoi(target),
		.sign = sign,
		.error = false,
	});
}
