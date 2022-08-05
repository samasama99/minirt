/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:04:40 by zsarir            #+#    #+#             */
/*   Updated: 2022/07/28 15:06:26 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"

double	magnitude(t_vec a)
{
	return (sqrt(dot(a, a)));
}

t_vec	scalar(t_vec a, double k)
{
	return ((t_vec){{
			a.x * k,
			a.y * k,
			a.z * k,
			a.w * k,}});
}

t_vec	normalize(t_vec v)
{
	t_vec			nv;
	const double	len = magnitude(v);
	double			invertlenght;

	if (len > 0 && len != 1)
	{
		invertlenght = 1 / len;
		nv = (t_vec){{
			.x = v.x * invertlenght,
			.y = v.y * invertlenght,
			.z = v.z * invertlenght,
			.w = 0, // careful
		}};
	}
	else
		nv = v;
	return (nv);
}

t_vec	opose(t_vec v)
{
	return ((t_vec){{
			v.x * -1,
			v.y * -1,
			v.z * -1,
			v.w * -1,}});
}
