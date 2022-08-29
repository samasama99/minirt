/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:38:45 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/23 12:48:06 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"
#include "main.h"
#include "parsing.h"

t_optional_material	parse_ambient(const t_optional_array elems)
{
	t_optional_double	ambient_ratio;
	t_optional_rgb		ambient_color;
	static bool			already_parsed = false;

	if (elems.error || already_parsed)
		return ((t_optional_material){.error = true});
	ambient_ratio = parse_ratio(elems.value[1]);
	ambient_color = parse_rgb(elems.value[2]);
	if (ambient_ratio.error || ambient_color.error)
		return ((t_optional_material){.error = true});
	already_parsed = true;
	return ((t_optional_material){
		.value = {
			.ambient_ratio = ambient_ratio.value,
			.ambient_color = ambient_color.value,
		},
		.error = false,
	});
}

t_optional_transform	get_camera_view(char *from, char *to)
{
	const t_optional_transform	error = {.error = true};
	t_optional_point			p_from;
	t_optional_point			p_to;
	t_vec						up;
	t_vec						direction;

	p_from = parse_position(from);
	p_to = parse_position(to);
	if (p_from.error || p_to.error)
		return (error);
	direction = sub(p_from.value, p_to.value);
	if (vec_is_equal(normalize(direction), vector(0, 1, 0))
		|| vec_is_equal(opose(normalize(direction)), vector(0, 1, 0)))
		up = vector(1, 0, 0);
	else
		up = vector(0, 1, 0);
	return ((t_optional_transform){
		.value = view_transform(p_from.value, p_to.value, up),
		.error = false,
	});
}

t_optional_camera	parse_camera(const t_optional_array elems, t_res res)
{
	const t_optional_camera	error = {.error = true};
	t_optional_transform	camera_view;
	t_camera				cam;
	t_optional_double		fov;
	static bool				already_parsed = false;

	if (elems.error || already_parsed)
		return (error);
	camera_view = get_camera_view(elems.value[1], elems.value[2]);
	fov = parse_fov(elems.value[3]);
	if (camera_view.error || fov.error)
		return (error);
	cam = camera(res.width, res.height, fov.value);
	cam.transform = camera_view.value;
	already_parsed = true;
	return ((t_optional_camera){
		.value = cam,
		.error = false,
	});
}

t_optional_light	parse_light(const t_optional_array elems)
{
	const t_optional_light	error = {.error = true};
	t_optional_point		pos;
	t_optional_double		brightness;
	t_optional_rgb			color;

	if (elems.error)
		return (error);
	pos = parse_position(elems.value[1]);
	brightness = parse_ratio(elems.value[2]);
	color = parse_rgb(elems.value[3]);
	if (pos.error || brightness.error || color.error)
		return (error);
	return ((t_optional_light){
		.value = point_light(pos.value,
			rgb_scalar(color.value, brightness.value)),
		.error = false,
	});
}

t_optional_shape	parse_plane(const t_optional_array elems)
{
	const t_optional_shape	error = {.error = true};
	t_optional_point		p;
	t_optional_point		normal;
	t_optional_rgb			color[2];
	t_plane					pl;

	if (elems.error)
		return (error);
	p = parse_position(elems.value[1]);
	normal = parse_position(elems.value[2]);
	color[0] = parse_rgb(elems.value[3]);
	color[1] = parse_rgb(elems.value[4]);
	if (p.error || normal.error || color[0].error)
		return (error);
	pl = plane();
	normal.value.w = 0;
	pl = make_plane(p.value, normal.value);
	pl.material = material();
	if (color[1].error)
		pl.material.color = color[0].value;
	else
	{
		pl.checkerboard_color1 = color[0].value;
		pl.checkerboard_color2 = color[1].value;
		pl.color_type = Checkerboard;
	}
	pl.transform = identity();
	return ((t_optional_shape){
		.value = (t_shape)pl,
		.error = false,
	});
}
