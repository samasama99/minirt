/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rt2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:18:52 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/21 14:45:11 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parsing.h"

t_shape	unwrap_shape(t_optional_array array, t_line_type type)
{
	const t_optional_shape	m = parse_shape(array, type);

	if (m.error)
		ft_exit(parse_string("failed to parse a shape"), 1);
	return (m.value);
}

