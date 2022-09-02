/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:08:11 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/01 19:15:36 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main.h>
#include <parsing.h>

static inline t_sphere	set_pattern(t_sphere s, t_rgb c1, t_rgb c2)
{
	s.color_type = Checkerboard;
	s.checkerboard_color1 = c1;
	s.checkerboard_color2 = c2;
	return (s);
}

static inline t_sphere	set_image(t_sphere s, t_image image)
{
	s.color_type = Texture;
	s.img = image;
	return (s);
}

t_optional_shape	parse_sphere(const t_optional_array elems)
{
	t_optional_point		center;
	t_optional_double		diameter;
	t_optional_rgb			color[2];
	t_optional_image		image;
	t_sphere				sp;

	if (elems.error || (elems.size != 4 && elems.size != 5))
		return ((t_optional_shape){.error = true});
	center = parse_position(elems.value[1]);
	diameter = parse_double(elems.value[2]);
	color[0] = parse_rgb(elems.value[3]);
	color[1] = parse_rgb(elems.value[4]);
	image = parse_image_path(elems.value[3]);
	if (center.error || diameter.error || (color[0].error && image.error))
		return ((t_optional_shape){.error = true});
	sp = make_sphere(center.value, diameter.value / 2.0, black());
	if (!color[0].error && color[1].error)
		sp.material.color = color[0].value;
	else if (color[1].error == false)
		sp = set_pattern(sp, color[0].value, color[1].value);
	else
		sp = set_image(sp, image.value);
	return ((t_optional_shape){.value = (t_shape)sp,});
}
