/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:32:48 by zsarir            #+#    #+#             */
/*   Updated: 2022/07/26 15:42:35 by zsarir           ###   ########.fr       */
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
	//   m.shininess = 0.0;
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

t_hit	cone_roots(double a, double b, double discriminant, t_cylinder cy)
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
	const double	a;
	const double	b;
	const double	c;
	const double	discriminant = b * b - 4 * a * c;

	if (discriminant < 0 || is_equal_double(a, 0))
		return (no_intersection());

	return (h);
}

t_vec	normal_at_cone(t_cone s, t_point local_point)
{
	return (normalize(vector(local_point.x, 0, local_point.z)));
}
 