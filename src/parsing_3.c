/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:38:40 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/09 21:39:18 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parsing.h"

t_optional_sphere	parse_sphere(const t_optional_array elems)
{
	const t_optional_sphere	error = {.error = true};
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
	return ((t_optional_sphere){
		.value = make_sphere(center.value,
			diameter.value / 2.0,
			color.value),
		.error = false,
	});
}

t_optional_cylinder	parse_cylinder(const t_optional_array elems)
{
	const t_optional_cylinder	error = {.error = true};
	t_optional_point			center;
	t_optional_point			normal;
	t_optional_double			diameter;
	t_optional_double			height;
	t_optional_rgb				color;
	t_cylinder					cy;

	if (elems.error)
		return (error);
	center = parse_position(elems.value[1]);
	normal = parse_position(elems.value[2]);
	diameter = parse_double(elems.value[3]);
	height = parse_double(elems.value[4]);
	color = parse_rgb(elems.value[5]);
	if (center.error || diameter.error || color.error)
		return (error);
	normal.value.w = 0;
	cy = make_cylinder(point(0, 0, 0), vector(0, 0, 0),
			(t_fpair){diameter.value / 2.0, height.value}, color.value);
	cy.t = mat4_mult(translation(center.value.x, center.value.y,
				center.value.z),
			mat4_mult(mat4_mult(rotation_x(acos(dot(normalize(normal.value),
								vector(0, 1, 0)))),
					rotation_z(acos(dot(vector(0, 1, 0),
								normalize(normal.value))))),
				rotation_y(acos(dot(normalize(normal.value),
							vector(1, 0, 0))))));
	return ((t_optional_cylinder){
		.value = cy,
		.error = false,
	});
}

t_optional_cone parse_cone(const t_optional_array elems)
{
	const t_optional_cone	error = {.error = true};
	t_optional_point		center;
	t_optional_point		normal;
	t_optional_double		diameter;
	t_optional_double		height;
	t_optional_rgb			color;
	t_cone					co;

	if (elems.error)
		return (error);
	center = parse_position(elems.value[1]);
	normal = parse_position(elems.value[2]);
	diameter = parse_double(elems.value[3]);
	height = parse_double(elems.value[4]);
	color = parse_rgb(elems.value[5]);
	if (center.error || diameter.error || color.error)
		return (error);
	normal.value.w = 0;
	co = make_cone(point(0, 0, 0), vector(0, 0, 0),
			(t_fpair){diameter.value / 2.0, height.value},
			color.value);
	co.t = mat4_mult(translation(center.value.x, center.value.y,
				center.value.z),
			mat4_mult(mat4_mult(rotation_x(acos(dot(normalize(normal.value),
								vector(0, 1, 0)))),
					rotation_z(acos(dot(vector(0, 1, 0),
								normalize(normal.value))))),
				rotation_y(acos(dot(normalize(normal.value),
							vector(1, 0, 0))))));
	return ((t_optional_cone){
		.value = co,
		.error = false,
	});
}

t_optional_shape    parse_shape(const t_optional_array elems, t_line_type type)
{
	t_optional_sphere	sp;
	t_optional_plane	pl;
	t_optional_cylinder	cy;
	t_optional_cone		co;

	if (!elems.error && type == e_sphere)
	{
		sp = parse_sphere(elems);
		if (sp.error)
			return ((t_optional_shape){.error = true});
		return ((t_optional_shape){
			.value = (t_shape)sp.value,
		});
	}
	if (!elems.error && type == e_plane)
	{
		pl = parse_plane(elems);
		if (pl.error)
			return ((t_optional_shape){.error = true});
		return ((t_optional_shape){
			.value = (t_shape)pl.value,
		});
	}
	if (!elems.error && type == e_cylinder)
	{
		cy = parse_cylinder(elems);
		if (cy.error)
			return ((t_optional_shape){.error = true});
		return ((t_optional_shape){
			.value = (t_shape)cy.value,
		});
	}
	if (!elems.error && type == e_cone)
	{
		co = parse_cone(elems);
		puts("found cone");
		if (co.error)
			return ((t_optional_shape){.error = true});
		return ((t_optional_shape){
			.value = (t_shape)co.value,
		});
    }
	return ((t_optional_shape){.value = true});
}
