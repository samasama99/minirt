/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:36:04 by zsarir            #+#    #+#             */
/*   Updated: 2022/09/04 17:10:20 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"
#include <main.h>

t_cone	make_cone(t_point point, t_norm norm,
					double height, t_rgb color)
{
	static int	id;
	t_material	m;

	m = material();
	m.color = color;
	return ((t_cone){
		.type = Cone,
		.id = ++id,
		.center = point,
		.height = height,
		.normal = norm,
		.t = identity(),
		.material = m,
		.color_type = Normal,
		.img = {.img = NULL, .buffer = NULL},
		.checkerboard_color1 = black(),
		.checkerboard_color2 = black(),
	});
}

t_hit	check_height_cone(const t_cone cy, const t_ray r, t_hit h)
{
	if (h.intersections[0].t <= 0 && h.intersections[1].t <= 0)
		return (no_intersection());
	if (fabs(ray_position(r, h.intersections[0].t).y - cy.center.y)
		> cy.height && fabs(ray_position(r, h.intersections[1].t).y
			- cy.center.y) > cy.height)
		return (no_intersection());
	if (fabs(ray_position(r, h.intersections[0].t).y - cy.center.y)
		<= cy.height && fabs(ray_position(r, h.intersections[1].t).y
			- cy.center.y) <= cy.height)
		return (h);
	if (fabs(ray_position(r, h.intersections[0].t).y - cy.center.y)
		<= cy.height)
		return ((t_hit){.intersections[0] = h.intersections[0], .count = 1});
	if (fabs(ray_position(r, h.intersections[1].t).y - cy.center.y)
		<= cy.height)
		return ((t_hit){.intersections[0] = h.intersections[1], .count = 1});
	return (no_intersection());
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
	const double	a = r.direction.x * r.direction.x - r.direction.y * r.direction.y +r.direction.z * r.direction.z;
	const double	b = 2 * (r.origin.x * r.direction.x - r.origin.y * r.direction.y + r.origin.z * r.direction.z);
	const double	c = r.origin.x * r.origin.x - r.origin.y * r.origin.y + r.origin.z * r.origin.z;

	if (discriminant(a, b, c) < 0)
		return (no_intersection());
	if (is_equal_double(a, 0))
		return (t_hit) {.intersections[0] = intersection(-c / (2 * b), (t_shape)co), .count = 1};
	return (check_height_cone(co, r,
		cone_roots(a, b, discriminant(a, b, c), co)));
}

t_vec	normal_at_cone(t_point p)
{
	double y = sqrt(p.x * p.x + p.z * p.z);	
	
	if (p.y > 0)
		y = -y;
	return vector(p.x, y, p.z);
}
