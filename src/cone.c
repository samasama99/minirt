/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:36:04 by zsarir            #+#    #+#             */
/*   Updated: 2022/07/28 16:09:43 by zsarir           ###   ########.fr       */
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
	});
}

t_cone	cone(void)
{
	return (make_cone(point(0, 0, 0), vector(0, 1, 0),
			(t_fpair){1, 1}, color(255, 0, 0)));
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
	const double			hi = co.center.y + co.height;

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
	const double	discriminant = b * b - 4 * a * c;

	if (discriminant < 0 || is_equal_double(a, 0))
		return (no_intersection());
	return (cone_roots(a, b, discriminant, co));
}

t_vec	normal_at_cone(t_cone s, t_point local_point)
{
	return (normalize(vector(local_point.x, 0, local_point.z)));
}
