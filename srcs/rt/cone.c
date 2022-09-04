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
	const t_vec x = sub(r.origin, co.center);
	const double m1 = dot(r.direction, scalar(co.normal, h.intersections[0].t)) + dot(x, co.normal);
	const double m2 = dot(r.direction, scalar(co.normal, h.intersections[1].t)) + dot(x, co.normal);

	if ((m1 > co.height && m2 > co.height) || (m1 < 0 && m2 < 0)) return no_intersection(); 
	if (m1 != m2){
		if (m2 >= 0 && m2 <= co.height && (m1 < 0 || m1 > co.height)) return (t_hit){.intersections[0] = h.intersections[1], .count = 1};
		if (m1 >=0 && m1 <= co.height && (m2 < 0 || m2 > co.height)) return (t_hit){.intersections[0] = h.intersections[0], .count = 1};
		if (m1 >= 0 && m2 >= 0 && m1 <= co.height && m2 <= co.height) return h;
	}
	else {
	if (m1 >= 0 && m1 <= co.height ) return (t_hit){.intersections[0] = h.intersections[0], .count = 1};
	}
	return no_intersection();
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
	const double	k = tan(radians(30));
	const double	a = dot(r.direction, r.direction) - (1 + k * k) * pow(dot(r.direction, (co.normal)), 2);
	const double	b = 2 * (dot(r.direction, sub(r.origin, co.center))
						-  (1 + k * k) * dot(r.direction, (co.normal)) * dot(sub(r.origin, co.center), (co.normal)));
	const double	c = dot(sub(r.origin, co.center), sub(r.origin, co.center))
							- (1 + k * k) * pow(dot(sub(r.origin, co.center), (co.normal)), 2);

	if (discriminant(a, b, c) < 0)
		return (no_intersection());
	return (check_height_cone(co, r,
			cone_roots(a, b, discriminant(a, b, c), co)));
}

t_vec	normal_at_cone(t_cone co, t_point p, const t_ray r)
{
	const t_vec x = sub(r.origin, co.center);
	const double	k = tan(radians(30));
	const double	t = sqrt((dot(p, p)- 2 * dot(p, r.origin) + dot(r.origin, r.origin)) / dot(r.direction, r.direction));
	const double 	m = dot(r.direction, scalar(co.normal, t)) + dot(x, co.normal);
	
	const t_vec		p_sub_center = sub(p, co.center);
	const t_vec		vm = scalar((co.normal), m);

	return normalize(sub(p_sub_cente, r(scalar(vm, (k * k + 1)))));
}
