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
	return (acos((p.y - sp.center.y) / sp.radius));
}

t_rad	phi_sphere(t_sphere sp, t_point p)
{
	return (atan2(sp.center.z - p.z, sp.center.x - p.x));
}

t_uv	uv_of_sphere(t_sphere sp, t_point p)
{
	const t_vec		vec = normalize(vector(-p.x + sp.center.x,
				-p.y + sp.center.y, -p.z + sp.center.z));
	const double	u = 0.5 + atan2(vec.x, vec.z) / (2 * M_PI);
	const double	v = 0.5 + asin(vec.y) / M_PI;

	return ((t_uv){-u, v});
}

t_uv	uv_of_plane(t_plane pl, t_point p)
{
	double	u;
	double	v;

	p = apply(inverse(pl.transform), p);
	u = fmod(p.x, 1);
	v = fmod(p.z, 1);
	return ((t_uv){u, -v});
}

t_uv	uv_cy(t_cylinder cy, t_point p)
{
	const t_vec		vec = vector(-p.x + cy.center.x,
			-p.y + cy.center.y, -p.z + cy.center.z);
	const double	teta = atan2(vec.x, vec.z);
	const double	u = 0.5 + (teta / (2 * M_PI));
	const double	v = 0.5 - clamp(vec.y / (floor(cy.height * 2)), -1, 1);

	return ((t_uv){u, v});
}


t_uv	uv_of_cylinder(t_cylinder cy, t_point p)
{
	return (uv_cy(cy, apply(inverse(cy.t), p)));
}
