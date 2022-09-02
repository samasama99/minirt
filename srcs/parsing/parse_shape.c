/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:38:40 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/30 17:26:21 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parsing.h"

t_optional_shape	parse_shape(const t_optional_array elems, t_line_type type)
{
	t_optional_shape	shape;

	shape = (t_optional_shape){.error = true};
	if (!elems.error && type == e_sphere)
		(printf(" \033[0;32m ----\033[0m :: parsing a sphere\n"),
			shape = parse_sphere(elems));
	if (!elems.error && type == e_plane)
		(printf(" \033[0;32m ----\033[0m :: parsing a plane\n"),
			shape = parse_plane(elems));
	if (!elems.error && type == e_cylinder)
		(printf(" \033[0;32m ----\033[0m :: parsing a cylinder\n"),
			shape = parse_cylinder(elems));
	if (!elems.error && type == e_cone)
		(printf(" \033[0;32m ----\033[0m :: parsing a cone\n"),
			shape = parse_cone(elems));
	if (shape.error == false)
		return ((t_optional_shape){.value = shape.value});
	return ((t_optional_shape){.error = true});
}

