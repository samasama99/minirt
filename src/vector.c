/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:48:42 by orahmoun          #+#    #+#             */
/*   Updated: 2022/07/28 15:05:03 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"

void	print_tupil(char *vec_name, t_vec a)
{
	printf("vec %s\n|x = %f|\n|y = %f|\n|z = %f|\n|w = %f|\n",
		vec_name, a.x, a.y, a.z, a.w);
}

t_vec	sum(t_vec a, t_vec b)
{
	return ((t_vec){{
			a.x + b.x,
			a.y + b.y,
			a.z + b.z,
			a.w + b.w,}});
}

t_vec	sub(t_vec a, t_vec b)
{
	return ((t_vec){{
			a.x - b.x,
			a.y - b.y,
			a.z - b.z,
			a.w - b.w,}});
}

inline double	dot(t_vec a, t_vec b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w));
}

inline t_vec	cross(t_vec a, t_vec b)
{
	return ((t_vec){{
			(a.y * b.z) - (a.z * b.y),
			(a.z * b.x) - (a.x * b.z),
			(a.x * b.y) - (a.y * b.x),
			0,}});
}
