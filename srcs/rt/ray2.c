/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:56:25 by zsarir            #+#    #+#             */
/*   Updated: 2022/09/04 14:12:07 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	is_inside_shape(t_vec normalv, t_vec eyev)
{
	return (dot(normalv, eyev) < 0);
}

t_comp	prepare_computations(t_intersection i, t_ray r)
{
	t_comp	comp;

	comp.r = r;
	comp.t = i.t;
	comp.shape = i.shape;
	comp.point = ray_position(r, comp.t);
	comp.eyev = opose(r.direction);
	comp.normalv = normal_at(comp.shape, comp.point);
	if (is_inside_shape(comp.normalv, comp.eyev))
	{
		comp.inside = true;
		comp.normalv = opose(comp.normalv);
	}
	else
		comp.inside = false;
	comp.over_point = sum(comp.point, scalar(comp.normalv, EPSILON));
	return (comp);
}
