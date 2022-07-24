/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 20:04:47 by zsarir            #+#    #+#             */
/*   Updated: 2022/07/24 20:55:45 by zsarir           ###   ########.fr       */
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

t_cylinder	cylinder(void)
{
	return (make_cylinder(point(0, 0, 0), vector(0, 1, 0),
			(t_fpair){1, 1}, color(255, 0, 0)));
}

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


t_hit	intersect_cylinder(const t_cylinder cy, const t_ray r)
{
	const double	a = pow(r.direction.x, 2) * pow(r.origin.z, 2);
	const double	b = 2 * (r.origin.x * r.direction.x + r.origin.z * r.direction.z);
	const double	c = pow(r.origin.z, 2) + pow(r.origin.x, 2) - pow(cy.radius, 2);
	const double	discriminant = b * b - 4 * a * c;

	if (discriminant < 0 || is_equal_double(a, 0))
		return (no_intersection());
	return (cylinder_roots(a, b, discriminant, cy));
}

t_vec	normal_at_cylinder(t_cylinder s, t_point local_point)
{
	return (normalize(vector(local_point.x, local_point.y, 0)));
}
