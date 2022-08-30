/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:20:22 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/27 19:20:23 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"
#include "main.h" 
#include <math.h>

t_rad	teta_sphere(t_sphere sp, t_point p)
{
	return (acos((p.y - sp.center.y)/ sp.radius));
}

t_rad	phi_sphere(t_sphere sp,t_point p)
{
	return (atan2(sp.center.z - p.z ,sp.center.x - p.x));
}

t_uv	uv_of_sphere(t_sphere sp, t_point p)
{
  t_vec vec =  {{-p.x + sp.center.x, -p.y + sp.center.y, -p.z + sp.center.z, 0}};
  vec = normalize(vec);
	double			u = 0.5 + atan2(vec.x, vec.z)  / (2 * M_PI);
	const double	v = 0.5 + asin(vec.y)/ M_PI;

	return ((t_uv){-u, v});
}

// t_uv uv_cy(t_cylinder cy, t_point p)
// {
// 	t_vec vec =  normalize(vector(-p.x + cy.center.x, -p.y + cy.center.y, -p.z + cy.center.z));
// 	double teta = atan2(p.x, p.z);
// 	double u = 1 - (teta / (2 * M_PI) + 0.5);
// 	double v = fmod(vec.y, 1);
// 	return (t_uv) {u, v};
// }

t_uv uv_of_plane(t_norm normal, t_point p)
{
	if (!is_equal_double(dot(normal, vector(1,0,0)), 0))
		p.x = p.y;
	if (!is_equal_double(dot(normal, vector(0,0,1)), 0))
		p.z = p.y;
	const double u = fmod(p.x, 1);
	const double v = fmod(p.z, 1);
	return (t_uv) {u, v};
}

t_uv uv_of_cylinder(t_cylinder cy, t_point p)
{
	t_point newp = apply(cy.t, p);
	t_point newc = apply(cy.t, cy.center);
	return uv_of_sphere(make_sphere(newc, cy.radius, color(1,1,1)), newp);
}
