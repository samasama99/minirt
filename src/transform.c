/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:40:26 by orahmoun          #+#    #+#             */
/*   Updated: 2022/07/28 15:03:38 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"

t_matrix4	translation(double x, double y, double z)
{
	return ((t_matrix4){{
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1,
		}});
}

t_matrix4	scaling(double x, double y, double z)
{
	return ((t_matrix4){{
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1,
		}});
}

t_rad	radians(t_deg deg)
{
	return (deg / 180 * M_PI);
}

t_matrix4	rotation_x(t_rad deg)
{
	return ((t_matrix4){{
			1, 0, 0, 0,
			0, cos(deg), -sin(deg), 0,
			0, sin(deg), cos(deg), 0,
			0, 0, 0, 1,
		}});
}

t_matrix4	rotation_y(t_rad deg)
{
	return ((t_matrix4){{
			cos(deg), 0, sin(deg), 0,
			0, 1, 0, 0,
			-sin(deg), 0, cos(deg), 0,
			0, 0, 0, 1,
		}});
}
