/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:36:04 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/15 12:56:05 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_cone	make_cone(t_point point, t_norm norm,
					t_fpair info, t_rgb color)
{
	static int	id;
	t_material	m;

	m = material();
	m.color = color;
	return ((t_cone){
		.type = Cone,
		.id = ++id,
		.center = point,
		.radius = info.x,
		.height = info.y,
		.normal = norm,
		.t = identity(),
		.material = m,
		.color_type = Normal,
		.img = {.img = NULL, .buffer = NULL},
		.checkerboard_color1 = black(),
		.checkerboard_color2 = black(),
	});
}

t_hit	check_height_cone(const t_cone co, const t_ray r, t_hit h)
{
	const double	hi = co.center.y + co.height;

	if (fabs(ray_position(r, h.intersections[0].t).y - hi) > co.height
		&& fabs(ray_position(r, h.intersections[1].t).y - hi) > co.height)
		return (no_intersection());
	if (fabs(ray_position(r, h.intersections[0].t).y - hi) <= co.height
		&& fabs(ray_position(r, h.intersections[1].t).y - hi) <= co.height)
		return (h);
	if (fabs(ray_position(r, h.intersections[0].t).y - hi) <= co.height)
		return ((t_hit){.intersections[0] = h.intersections[0], .count = 1});
	if (fabs(ray_position(r, h.intersections[1].t).y - hi) <= co.height)
		return ((t_hit){.intersections[0] = h.intersections[1], .count = 1});
	return (h);
}

t_hit	cone_roots(double a, double b, double discriminant, t_cone co)
{
	const double			sqrt_dis = sqrt(discriminant);
	const double			root1 = ((-1 * b) - sqrt_dis) / (2 * a);
	const double			root2 = ((-1 * b) + sqrt_dis) / (2 * a);
	const t_intersection	is[2] = {
		intersection(root1, (t_shape)co),
		intersection(root2, (t_shape)co),
	};

	return ((t_hit){{is[0], is[1]}, 2});
}

t_hit	intersect_cone(const t_cone co, const t_ray r)
{
	const double	k = co.radius / co.height;
	const double	a = pow(r.direction.x, 2) + pow(r.direction.z, 2)
		- pow(k, 2) * pow(r.direction.y, 2);
	const double	b = 2 * (r.origin.x * r.direction.x
			+ r.origin.z * r.direction.z
			- r.origin.y * r.direction.y * pow(k, 2)
			- r.direction.x * co.center.x - r.direction.z * co.center.z
			+ co.height * pow(k, 2) * r.direction.y);
	const double	c = pow(r.origin.x, 2) + pow(r.origin.z, 2)
		- pow(r.origin.y, 2) * pow(k, 2)
		- 2 * (r.origin.x * co.center.x + r.origin.z * co.center.z)
		- pow(co.height, 2) * pow(k, 2)
		+ 2 * co.height * pow(k, 2) * r.origin.y;

	if (discriminant < 0 || is_equal_double(a, 0))
		return (no_intersection());
	return (check_height_cone(co, r,
			cone_roots(a, b, discriminant(a, b, c), co)));
}

t_vec	normal_at_cone(t_point local_point)
{
	return (normalize(vector(local_point.x, 0, local_point.z)));
}
