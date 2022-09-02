/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:04:31 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/02 16:10:06 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

inline t_transform	set_transform(t_point p, t_norm normal)
{
	const double	normal_dot_y = dot(normalize(normal),
			vector(0, 1, 0));
	const double	normal_dot_z = dot(normalize(normal),
			vector(0, 0, 1));		

	return (mat4_mult(translation(p.x, p.y, p.z),
			mat4_mult(mat4_mult(rotation_y(acos(normal_dot_z)),
					rotation_z(acos(normal_dot_y))),
				rotation_x(acos(normal_dot_y)))));
}
