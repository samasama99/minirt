/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:03:35 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/03 14:09:33 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <parsing.h>

static inline t_plane	set_pattern(t_plane s, t_rgb c1, t_rgb c2)
{
	s.color_type = Checkerboard;
	s.checkerboard_color1 = c1;
	s.checkerboard_color2 = c2;
	return (s);
}

static inline t_plane	set_image(t_plane s, t_image image)
{
	s.color_type = Texture;
	s.img = image;
	return (s);
}

t_optional_shape	parse_plane(const t_optional_array elems)
{
	t_optional_point	p;
	t_optional_vector	normal;
	t_optional_rgb		color[2];
	t_optional_image	image;
	t_plane				pl;

	if (elems.error || (elems.size != 4 && elems.size != 5))
		return ((t_optional_shape){.error = true});
	p = parse_position(elems.value[1]);
	normal = parse_vector(elems.value[2]);
	color[0] = parse_rgb(elems.value[3]);
	image = parse_image_path(elems.value[3]);
	color[1] = parse_rgb(elems.value[4]);
	if (p.error || normal.error || (color[0].error && image.error))
		return ((t_optional_shape){.error = true});
	normal.value.w = 0;
	pl = make_plane(point(0, 0, 0), vector(0, 1, 0));
	pl.material = material();
	pl.material.color = color[0].value;
	if (color[1].error == false)
		pl = set_pattern(pl, color[0].value, color[1].value);
	else if (image.error == false)
		pl = set_image(pl, image.value);
	pl.transform = set_transform(p.value, normal.value);
	return (pl.material.specular = 0, (t_optional_shape){.value = (t_shape)pl});
}
