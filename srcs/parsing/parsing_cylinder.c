/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:00:41 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/02 16:01:09 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parsing.h"

typedef struct s_optional_cylinder_infos {
	t_optional_point			center;
	t_optional_vector			normal;
	t_optional_double			diameter;
	t_optional_double			height;
}		t_optional_cylinder_info;

static inline t_cylinder	set_pattern(t_cylinder s, t_rgb c1, t_rgb c2)
{
	s.color_type = Checkerboard;
	s.checkerboard_color1 = c1;
	s.checkerboard_color2 = c2;
	return (s);
}

static inline t_cylinder	set_image(t_cylinder s, t_image image)
{
	s.color_type = Texture;
	s.img = image;
	return (s);
}

t_optional_shape	parse_cylinder(const t_optional_array elems)
{
	t_optional_cylinder_info	i;
	t_optional_image			image;
	t_optional_rgb				col[2];
	t_cylinder					cy;

	if (elems.error || (elems.size != 6 && elems.size != 7))
		return ((t_optional_shape){.error = true});
	i.center = parse_position(elems.value[1]);
	i.normal = parse_vector(elems.value[2]);
	i.diameter = parse_double(elems.value[3]);
	i.height = parse_double(elems.value[4]);
	col[0] = parse_rgb(elems.value[5]);
	image = parse_image_path(elems.value[5]);
	col[1] = parse_rgb(elems.value[6]);
	if (i.center.error || i.diameter.error || (col[0].error && image.error))
		return ((t_optional_shape){.error = true});
	cy = make_cylinder(point(0, 0, 0), vector(0, 1, 0),
			(t_fpair){{i.diameter.value / 2.0, i.height.value}}, col[0].value);
	cy.t = set_transform(i.center.value, i.normal.value);
	if (col[1].error == false)
		cy = set_pattern(cy, col[0].value, col[1].value);
	else if (image.error == false)
		cy = set_image(cy, image.value);
	return ((t_optional_shape){.value = (t_shape)cy, .error = false});
}
