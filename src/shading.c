/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 16:44:23 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/27 19:18:43 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"
#include "main.h"
#include "parsing.h"

t_rgb	ambient(t_material m, t_light l);

int get_color_at(t_image img, int x, int y)
{
  return (img.buffer[x + (y * img.res.width)]);
}

t_rgb shade_hit_normal(t_world w, t_comp comps, t_light l) {
	double				reflect_dot_eye;
	const t_material	m = comps.shape.super.material;
	t_vec				reflectv;
	const t_vec			lightv = normalize(
			sub(l.position, comps.over_point));
	const double		light_dot_normal = dot(lightv, comps.normalv);

	if (is_shadowed(w, comps.over_point, l) == true
		|| light_dot_normal < 0)
		return ambient(m, l);
	reflectv = reflect(opose(lightv), comps.normalv);
	reflect_dot_eye = dot(reflectv, comps.eyev);
	return (lighting(
			m,
			l,
			light_dot_normal,
			reflect_dot_eye));
}

t_rgb shade_hit_texture(t_world w, t_comp comps, t_light l, t_intersection	inter) {

	if (inter.shape.type == Sphere)
		return shade_hit_bm_sphere(comps, l, inter.shape.sphere, w);
	puts("bm_normal_at unknown shape"), exit(1);
	return black();
};

t_rgb shade_hit_checkerboard(t_point p, t_shape shape) {
	t_uv	uv;
	t_pair	ab;

	uv = (t_uv) {0,0};
	ab = pair(0, 0);
	if (shape.type == Sphere)
		uv = uv_of_sphere(shape.sphere, p), ab = pair(30, 30);
	else if (shape.type == Plane)
		uv = uv_of_plane(shape.plane, p), ab = pair(10, 10);
	else if (shape.type == Cylinder)
		uv = uv_of_cylinder(shape.cylinder, p), ab = pair(50, 50);
	else
		ft_exit(parse_string("uv : checkerboard : unknown type\n"), 1);
	return checkerboard(uv,
					 shape.super.checkerboard_color1,
					 shape.super.checkerboard_color2,
					 ab);
};

t_vec	reflect(t_vec in, t_vec norm)
{
	return (sub(in, scalar(norm, 2.0 * dot(in, norm))));
}

bool	is_shadowed(t_world w, t_point p, t_light l)
{
	const t_vec				v = sub(l.position, p);
	const double			d = magnitude(v);
	const t_vec				direction = normalize(v);
	const t_ray				r = ray(p, direction);
	const t_intersection	i = intersect_world(w, r).intersections[0];

	return ((i.t >= 0 && i.t < d) == true);
}

t_rgb	color_at(t_world w, t_ray r)
{
	const t_hit		h = intersect_world(w, r);
	t_rgb			c;
	t_comp			comps;
	t_intersection	inter;
	int				index;

	c = black();
	index = 0;
	if (h.count == 0)
		return (c);
	inter = hit(h);
	if (inter.t < 0)
		return (c);
	while (index < w.amount_of_lights)
	{
		comps = prepare_computations(inter, r);
		if (inter.shape.super.color_type == Normal)
			c = rgb_sum(shade_hit_normal(w, comps, w.lights[index]), c);
		else if (inter.shape.super.color_type == Checkerboard)
		{
			c = shade_hit_checkerboard(comps.over_point, inter.shape);
			// break ;
		}
		else if (inter.shape.super.color_type == Texture)
		{
			c = shade_hit_texture(w, comps, w.lights[index], inter);
			// break;
		}
		++index;
	}
	if (inter.shape.super.color_type == Normal) {
		c = rgb_sub(c, rgb_scalar(
			rgb_scalar(inter.shape.super.material.ambient_color,
				inter.shape.super.material.ambient_ratio),
			w.amount_of_lights - 1));
	}
	return (c);
}
