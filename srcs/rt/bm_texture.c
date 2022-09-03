/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bm_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:31:30 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/03 14:07:08 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linear_algebra.h>
#include <main.h>
#include <math.h>

t_rgb	t_color_to_t_rgb(t_color ucolor)
{
	return (color((float)ucolor.red / 255.999,
			(float)ucolor.green / 255.999,
			(float)ucolor.blue / 255.999));
}

t_rgb	shade_hit_bm_sphere(t_comp comps, t_light l, t_sphere s, t_world w)
{
	const t_uv		uv = uv_of_sphere(s, comps.over_point);
	const t_fpair	ij = ij_of_map(s.img.res, uv);
	const t_color	ucolor = (t_color)(int)get_color_at(s.img, ij.i, ij.j);
	const t_vec		lightv = normalize(sub(l.position, comps.over_point));

	if (is_shadowed(w, comps.over_point, l) == true
		|| dot(lightv, comps.normalv) < 0)
		return (black());
	s.material.color = t_color_to_t_rgb(ucolor);
	return (diffuse(s.material, l,
			dot(lightv, comps.normalv)));
}

t_rgb	shade_hit_bm_cylinder(t_comp comps, t_light l, t_cylinder s, t_world w)
{
	const t_uv		uv = uv_of_cylinder(s, comps.over_point);
	const t_fpair	ij = ij_of_map(s.img.res, uv);
	const t_color	ucolor = (t_color)(int)get_color_at(s.img, ij.i, ij.j);
	const t_vec		lightv = normalize(sub(l.position, comps.over_point));

	if (is_shadowed(w, comps.over_point, l) == true
		|| dot(lightv, comps.normalv) < 0)
		return (black());
	s.material.color = t_color_to_t_rgb(ucolor);
	return (diffuse(s.material, l,
			dot(lightv, comps.normalv)));
}

t_rgb	shade_hit_bm_plane(t_comp comps, t_light l, t_plane s, t_world w)
{
	const t_uv		uv = uv_of_plane(s, comps.over_point);
	const t_fpair	ij = ij_of_map(s.img.res, uv);
	const t_color	ucolor = (t_color)(int)get_color_at(s.img, ij.i, ij.j);
	const t_vec		lightv = normalize(sub(l.position, comps.over_point));

	if (is_shadowed(w, comps.over_point, l) == true
		|| dot(lightv, comps.normalv) < 0)
		return (black());
	s.material.color = t_color_to_t_rgb(ucolor);
	return (diffuse(s.material, l,
			dot(lightv, comps.normalv)));
}
