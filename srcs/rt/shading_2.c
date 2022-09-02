/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:16:40 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/02 16:27:42 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <main.h>

bool	is_shadowed(t_world w, t_point p, t_light l)
{
	const t_vec				v = sub(l.position, p);
	const double			d = magnitude(v);
	const t_vec				direction = normalize(v);
	const t_ray				r = ray(p, direction);
	const t_intersection	i = intersect_world(w, r).intersections[0];

	return ((i.t >= 0 && i.t < d) == true);
}

t_rgb	correct_ambient_over_calc(t_rgb c, t_shape s, t_world w)
{
	const t_rgb	ambient_color = rgb_scalar(s.super.material.ambient_color,
			s.super.material.ambient_ratio);

	if (s.super.color_type == Normal && w.amount_of_lights > 1)
		return (rgb_sub(c, rgb_scalar(ambient_color,
					w.amount_of_lights - 1)));
	return (c);
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
			c = shade_hit_checkerboard(comps.over_point, inter.shape);
		else if (inter.shape.super.color_type == Texture)
			c = shade_hit_texture(w, comps, w.lights[index], inter);
		++index;
	}
	return (correct_ambient_over_calc(c, inter.shape, w));
}