/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fov.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:01:21 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/02 16:01:22 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

t_optional_double	parse_fov(const char *target)
{
	t_optional_int	deg;

	deg = parse_int(target);
	if (deg.error)
		return ((t_optional_double){.error = true});
	if (deg.value < 0 || deg.value > 180)
		return ((t_optional_double){.error = true});
	return ((t_optional_double){
		.value = radians(deg.value),
		.error = false,
	});
}
