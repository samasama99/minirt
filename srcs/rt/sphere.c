/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:40:18 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/02 16:20:15 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_sphere	make_sphere(t_point origin, double radius, t_rgb color)
{
	static int	id;
	t_material	m;

	m = material();
	m.color = color;
	return ((t_sphere){
		.type = Sphere,
		.id = ++id,
		.t = identity(),
		.material = m,
		.color_type = Normal,
		.img = {.img = NULL, .buffer = NULL},
		.checkerboard_color1 = black(),
		.checkerboard_color2 = black(),
		.center = origin,
		.radius = radius,
	});
}

t_hit	sphere_roots(double a, double b, double discriminant, t_sphere sp)
{
	const double			sqrt_dis = sqrt(discriminant);
	const double			root1 = ((-1 * b) - sqrt_dis) / (2 * a);
	const double			root2 = ((-1 * b) + sqrt_dis) / (2 * a);
	const t_intersection	is[2] = {
		intersection(root1, (t_shape)sp),
		intersection(root2, (t_shape)sp),
	};

	return ((t_hit){{is[0], is[1]}, 2});
}

t_hit	intersect_sphere(const t_sphere sp, const t_ray r)
{
	const t_vec		e_c = sub(r.origin, sp.center);
	const double	a = dot(r.direction, r.direction);
	const double	b = 2.0 * dot(e_c, r.direction);
	const double	c = dot(e_c, e_c) - sp.radius * sp.radius;
	const double	discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (no_intersection());
	return (sphere_roots(a, b, discriminant, sp));
}

t_vec	normal_at_sphere(t_sphere s, t_point local_point)
{
	return (sub(local_point, s.center));
}
