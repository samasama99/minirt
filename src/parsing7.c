/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:38:40 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/23 19:54:40 by orahmoun         ###   ########.fr       */
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
	t_optional_rgb			color[2];
	t_optional_image			image;
  	t_sphere sp;

	if (elems.error)
		return (error);
	center = parse_position(elems.value[1]);
	diameter = parse_double(elems.value[2]);
	color[0] = parse_rgb(elems.value[3]);
	color[1] = parse_rgb(elems.value[4]);
  	image = parse_image_path(elems.value[3]);

	if (center.error || diameter.error || (color[0].error && image.error))
		return (error);
    sp = make_sphere(center.value,
      diameter.value / 2.0,
      black());
    if (color[0].error == false) {
		if (color[1].error)
        	sp.material.color = color[0].value;
		else
		{
			sp.color_type = Checkerboard;
			sp.checkerboard_color1 = color[0].value;
			sp.checkerboard_color2 = color[1].value;
		}
    }
    else
    {
      sp.color_type = Texture;
      sp.img = image.value;
    }
  return ((t_optional_shape){
    .value = (t_shape)sp,
    .error = false,
  });
}

t_optional_shape	parse_cylinder(const t_optional_array elems)
{
	const t_optional_shape		error = {.error = true};
	t_optional_cylinder_info	i;
	t_optional_rgb						color2;

	if (elems.error)
		return (error);
	i.center = parse_position(elems.value[1]);
	i.normal = parse_position(elems.value[2]);
	i.diameter = parse_double(elems.value[3]);
	i.height = parse_double(elems.value[4]);
	i.color = parse_rgb(elems.value[5]);
	color2 = parse_rgb(elems.value[6]);
	if (i.center.error || i.diameter.error || i.color.error)
		return (error);
	i.normal.value.w = 0;
	i.cy = make_cylinder(point(0, 0, 0), vector(0, 0, 0),
			(t_fpair){{i.diameter.value / 2.0, i.height.value}}, i.color.value);
	i.cy.t = mat4_mult(translation(i.center.value.x, i.center.value.y,
				i.center.value.z),
			mat4_mult(mat4_mult(rotation_x(acos(dot(normalize(i.normal.value),
								vector(0, 1, 0)))),
					rotation_z(acos(dot(vector(0, 1, 0),
								normalize(i.normal.value))))),
				rotation_y(acos(dot(normalize(i.normal.value),
							vector(1, 0, 0))))));
	if (color2.error)
		i.cy.material.color = i.color.value;
	else
	{
		i.cy.checkerboard_color1 = i.color.value;
		i.cy.checkerboard_color2 = color2.value;
		i.cy.color_type = Checkerboard;
	}
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
			(t_fpair){{i.diameter.value / 2.0, i.height.value}},
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

	shape = (t_optional_shape){.error = true};
	if (!elems.error && type == e_sphere)
		(printf(" \033[0;32m----\033[0m :: parsing a sphere\n"),
			shape = parse_sphere(elems));
	if (!elems.error && type == e_plane)
		(printf(" \033[0;32m----\033[0m :: parsing a plane\n"),
			shape = parse_plane(elems));
	if (!elems.error && type == e_cylinder)
		(printf(" \033[0;32m----\033[0m :: parsing a cylinder\n"),
			shape = parse_cylinder(elems));
	if (!elems.error && type == e_cone)
		(printf(" \033[0;32m----\033[0m :: parsing a cone\n"),
			shape = parse_cone(elems));
	if (shape.error == false)
		return ((t_optional_shape){.value = shape.value});
	return ((t_optional_shape){.error = true});
}

