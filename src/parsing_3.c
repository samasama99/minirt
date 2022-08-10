/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:38:40 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/10 11:49:38 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parsing.h"

typedef struct s_optional_cylinder_infos {
	t_optional_point			center;
	t_optional_point			normal;
	t_optional_double			diameter;
	t_optional_double			height;
	t_optional_rgb				color;
	t_cylinder					cy;
}		t_optional_cylinder_info;

typedef struct s_optional_cone_infos {
	t_optional_point		center;
	t_optional_point		normal;
	t_optional_double		diameter;
	t_optional_double		height;
	t_optional_rgb			color;
	t_cone					co;
}		t_optional_cone_info;

t_optional_shape	parse_sphere(const t_optional_array elems)
{
	const t_optional_shape	error = {.error = true};
	t_optional_point		center;
	t_optional_double		diameter;
	t_optional_rgb			color;

	if (elems.error)
		return (error);
	center = parse_position(elems.value[1]);
	diameter = parse_double(elems.value[2]);
	color = parse_rgb(elems.value[3]);
	if (center.error || diameter.error || color.error)
		return (error);
	return ((t_optional_shape){
		.value = (t_shape)make_sphere(center.value,
			diameter.value / 2.0,
			color.value),
		.error = false,
	});
}

t_optional_shape	parse_cylinder(const t_optional_array elems)
{
	const t_optional_shape		error = {.error = true};
	t_optional_cylinder_info	i;

	if (elems.error)
		return (error);
	i.center = parse_position(elems.value[1]);
	i.normal = parse_position(elems.value[2]);
	i.diameter = parse_double(elems.value[3]);
	i.height = parse_double(elems.value[4]);
	i.color = parse_rgb(elems.value[5]);
	if (i.center.error || i.diameter.error || i.color.error)
		return (error);
	i.normal.value.w = 0;
	i.cy = make_cylinder(point(0, 0, 0), vector(0, 0, 0),
			(t_fpair){i.diameter.value / 2.0, i.height.value}, i.color.value);
	i.cy.t = mat4_mult(translation(i.center.value.x, i.center.value.y,
				i.center.value.z),
			mat4_mult(mat4_mult(rotation_x(acos(dot(normalize(i.normal.value),
								vector(0, 1, 0)))),
					rotation_z(acos(dot(vector(0, 1, 0),
								normalize(i.normal.value))))),
				rotation_y(acos(dot(normalize(i.normal.value),
							vector(1, 0, 0))))));
	return ((t_optional_shape){.value = (t_shape)i.cy, .error = false});
}

t_optional_shape	parse_cone(const t_optional_array elems)
{
	const t_optional_shape	error = {.error = true};
	t_optional_cone_info	i;

	if (elems.error)
		return (error);
	i.center = parse_position(elems.value[1]);
	i.normal = parse_position(elems.value[2]);
	i.diameter = parse_double(elems.value[3]);
	i.height = parse_double(elems.value[4]);
	i.color = parse_rgb(elems.value[5]);
	if (i.center.error || i.diameter.error || i.color.error)
		return (error);
	i.normal.value.w = 0;
	i.co = make_cone(point(0, 0, 0), vector(0, 0, 0),
			(t_fpair){i.diameter.value / 2.0, i.height.value},
			i.color.value);
	i.co.t = mat4_mult(translation(i.center.value.x, i.center.value.y,
				i.center.value.z),
			mat4_mult(mat4_mult(rotation_x(acos(dot(normalize(i.normal.value),
								vector(0, 1, 0)))),
					rotation_z(acos(dot(vector(0, 1, 0),
								normalize(i.normal.value))))),
				rotation_y(acos(dot(normalize(i.normal.value),
							vector(1, 0, 0))))));
	return ((t_optional_shape){.value = (t_shape)i.co, .error = false});
}

t_optional_shape	parse_shape(const t_optional_array elems, t_line_type type)
{
	t_optional_shape	shape;

	shape = (t_optional_shape){.value = true};
	if (!elems.error && type == e_sphere)
		(printf("parsing a sphere\n"), shape = parse_sphere(elems));
	if (!elems.error && type == e_plane)
		(printf("parsing a plane\n"), shape = parse_plane(elems));
	if (!elems.error && type == e_cylinder)
		(printf("parsing a cylinder\n"), shape = parse_cylinder(elems));
	if (!elems.error && type == e_cone)
		(printf("parsing a cone\n"), shape = parse_cone(elems));
	if (shape.error == false)
		return ((t_optional_shape){.value = shape.value});
	return ((t_optional_shape){.error = true});
}
