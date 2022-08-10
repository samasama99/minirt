/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 20:04:47 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/10 11:43:41 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_cylinder	make_cylinder(t_point point, t_norm norm,
							t_fpair info, t_rgb color)
{
	static int	id;
	t_material	m;

	m = material();
	m.color = color;
	return ((t_cylinder){
		.type = Cylinder,
		.id = ++id,
		.center = point,
		.radius = info.x,
		.height = info.y,
		.normal = norm,
		.t = identity(),
		.material = m,
	});
}

// t_cylinder	cylinder(void)
// {
// 	return (make_cylinder(point(0, 0, 0), vector(0, 1, 0),
// 			(t_fpair){1, 1}, color(255, 0, 0)));
// }

t_hit	cylinder_roots(double a, double b, double discriminant, t_cylinder cy)
{
	const double			sqrt_dis = sqrt(discriminant);
	const double			root1 = ((-1 * b) - sqrt_dis) / (2 * a);
	const double			root2 = ((-1 * b) + sqrt_dis) / (2 * a);
	const t_intersection	is[2] = {
		intersection(root1, (t_shape)cy),
		intersection(root2, (t_shape)cy),
	};

	return ((t_hit){{is[0], is[1]}, 2});
}

t_hit	check_height_cylinder(const t_cylinder cy, const t_ray r, t_hit h)
{
	if (fabs(ray_position(r, h.intersections[0].t).y - cy.center.y)
		> cy.height / 2 && fabs(ray_position(r, h.intersections[1].t).y
			- cy.center.y) > cy.height / 2)
		return (no_intersection());
	if (fabs(ray_position(r, h.intersections[0].t).y - cy.center.y)
		<= cy.height / 2 && fabs(ray_position(r, h.intersections[1].t).y
			- cy.center.y) <= cy.height / 2)
		return (h);
	if (fabs(ray_position(r, h.intersections[0].t).y - cy.center.y)
		<= cy.height / 2)
		return ((t_hit){.intersections[0] = h.intersections[0], .count = 1});
	if (fabs(ray_position(r, h.intersections[1].t).y - cy.center.y)
		<= cy.height / 2)
		return ((t_hit){.intersections[0] = h.intersections[1], .count = 1});
	return (h);
}

t_hit	intersect_cylinder(const t_cylinder cy, const t_ray r)
{
	const double	a = pow(r.direction.x, 2) + pow(r.direction.z, 2);
	const double	b = 2 * (r.origin.x * r.direction.x
			+ r.origin.z * r.direction.z
			- r.direction.x * cy.center.x
			- r.direction.z * cy.center.z);
	const double	c = pow(r.origin.z, 2) + pow(r.origin.x, 2)
		- pow(cy.radius, 2) + pow(cy.center.x, 2) + pow(cy.center.z, 2)
		- 2 * (r.origin.x * cy.center.x + r.origin.z * cy.center.z);

	if (discriminant(a, b, c) < 0 || is_equal_double(a, 0))
		return (no_intersection());
	return (check_height_cylinder(cy, r,
			cylinder_roots(a, b, discriminant(a, b, c), cy)));
}

t_vec	normal_at_cylinder(t_cylinder s, t_point local_point)
{
	return (normalize(vector(local_point.x, 0, local_point.z)));
}
