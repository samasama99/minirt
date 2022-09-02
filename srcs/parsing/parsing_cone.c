/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:59:45 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/02 17:48:01 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <parsing.h>

typedef struct s_optional_cone_infos {
	t_optional_point		center;
	t_optional_vector		normal;
	t_optional_double		diameter;
	t_optional_double		height;
}		t_optional_cone_info;

t_optional_shape	parse_cone(const t_optional_array elems)
{
	const t_optional_shape	error = {.error = true};
	t_optional_rgb			color;
	t_cone					co;
	t_optional_cone_info	i;

	if (elems.error || (elems.size != 7))
		return (error);
	i.center = parse_position(elems.value[1]);
	i.normal = parse_vector(elems.value[2]);
	i.diameter = parse_double(elems.value[3]);
	i.height = parse_double(elems.value[4]);
	color = parse_rgb(elems.value[5]);
	if (i.center.error || i.diameter.error || color.error)
		return (error);
	i.normal.value.w = 0;
	co = make_cone(point(0, 0, 0), vector(0, 1, 0),
			(t_fpair){{i.diameter.value / 2.0, i.height.value}}, color.value);
	co.t = set_transform(i.center.value, i.normal.value);
	return ((t_optional_shape){.value = (t_shape)co, .error = false});
}
