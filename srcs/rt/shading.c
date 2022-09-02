/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 16:44:23 by zsarir            #+#    #+#             */
/*   Updated: 2022/09/02 16:18:57 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linear_algebra.h>
#include <main.h>
#include <parsing.h>

int	get_color_at(t_image img, int x, int y)
{
	x = x % img.res.width;
	if (x < 0)
		x += img.res.width;
	y = y % img.res.height;
	if (y < 0)
		y += img.res.height;
	return (img.buffer[x + (y * img.res.width)]);
}

t_rgb	shade_hit_normal(t_world w, t_comp comps, t_light l)
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

t_rgb	shade_hit_texture(t_world w,
						t_comp comps,
						t_light l,
						t_intersection inter)
{
	if (inter.shape.type == Sphere)
		return (shade_hit_bm_sphere(comps, l, inter.shape.sphere, w));
	else if (inter.shape.type == Cylinder)
		return (shade_hit_bm_cylinder(comps, l, inter.shape.cylinder, w));
	else if (inter.shape.type == Plane)
		return (shade_hit_bm_plane(comps, l, inter.shape.plane, w));
	puts("shade_hit_texture unknown shape");
	exit(1);
	return (black());
}

t_rgb	shade_hit_checkerboard(t_point p, t_shape shape)
{
	t_uv	uv;
	t_pair	ab;

	uv = (t_uv){0, 0};
	ab = pair(0, 0);
	if (shape.type == Sphere)
	{
		uv = uv_of_sphere(shape.sphere, p);
		ab = pair(30, 30);
	}
	else if (shape.type == Plane)
	{
		uv = uv_of_plane(shape.plane, p);
		ab = pair(10, 10);
	}
	else if (shape.type == Cylinder)
	{
		uv = uv_of_cylinder(shape.cylinder, p);
		ab = pair(5, 5);
	}
	else
		ft_exit(parse_string("uv : checkerboard : unknown type\n"), 1);
	return (checkerboard(uv,
			shape.super.checkerboard_color1,
			shape.super.checkerboard_color2,
			ab));
}

t_vec	reflect(t_vec in, t_vec norm)
{
	return (sub(in, scalar(norm, 2.0 * dot(in, norm))));
}
