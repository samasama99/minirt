/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unwrap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:59:20 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/01 18:59:21 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

t_shape	unwrap_shape(t_optional_array array, t_line_type type)
{
	const t_optional_shape	m = parse_shape(array, type);

	if (m.error)
		ft_exit(parse_string("failed to parse a shape"), 1);
	return (m.value);
}

t_camera	unwarp_camera(t_optional_array array, t_res res)
{
	const t_optional_camera	c = parse_camera(array, res);

	if (c.error)
		ft_exit(parse_string("failed to parse the camera"), 1);
	return (c.value);
}

t_light	unwrap_light(t_optional_array array)
{
	const t_optional_light	l = parse_light(array);

	if (l.error)
		ft_exit(parse_string("failed to parse the light"), 1);
	return (l.value);
}

t_material	unwrap_ambient(t_optional_array array)
{
	const t_optional_material	m = parse_ambient(array);

	if (m.error)
		ft_exit(parse_string("failed to parse the ambient"), 1);
	return ((t_material){
		.ambient_color = m.value.ambient_color,
		.ambient_ratio = m.value.ambient_ratio,
	});
}
