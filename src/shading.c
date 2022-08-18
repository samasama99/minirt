/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:40:04 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/18 22:06:40 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_rgb	ambient(t_material m, t_light l);

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
	t_comp			comp;
	t_intersection	i;
	int				index;

	c = black();
	index = 0;
	if (h.count == 0)
		return (c);
	i = hit(h);
	if (i.t < 0)
		return (c);
	while (index < w.amount_of_lights)
	{
		comp = prepare_computations(i, r);
		c = rgb_sum(shade_hit(w, comp, w.lights[index]), c);
		++index;
	}
	c = rgb_sub(c, rgb_scalar(
				rgb_scalar(i.shape.super.material.ambient_color,
					i.shape.super.material.ambient_ratio),
				w.amount_of_lights - 1));
	return (c);
}

t_rgb	shade_hit(t_world w, t_comp comps, t_light l)
{
	double				reflect_dot_eye;
	const t_material	m = comps.shape.super.material;
	t_vec				reflectv;
	const t_vec			lightv = normalize(
			sub(l.position, comps.over_point));
	const double		light_dot_normal = dot(lightv, comps.normalv);

	if (is_shadowed(w, comps.over_point, l) == true
		|| light_dot_normal < 0)
		return (ambient(m, l));
	reflectv = reflect(opose(lightv), comps.normalv);
	reflect_dot_eye = dot(reflectv, comps.eyev);
	return (lighting(
			m,
			l,
			light_dot_normal,
			reflect_dot_eye));
}
