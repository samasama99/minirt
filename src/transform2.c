/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:03:18 by zsarir            #+#    #+#             */
/*   Updated: 2022/07/28 15:03:43 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"

t_matrix4	rotation_z(t_rad deg)
{
	return ((t_matrix4){{
			cos(deg), -sin(deg), 0, 0,
			sin(deg), cos(deg), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
		}});
}

t_matrix4	transform(t_matrix4 a, t_matrix4 b, t_matrix4 c)
{
	const t_transform	f = mat4_mult(b, a);

	return (mat4_mult(c, f));
}

inline t_matrix4	identity(void)
{
	return ((t_matrix4){{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
		}});
}

t_transform	view_transform(t_point from, t_point to, t_vec up)
{
	const t_vec			forward = normalize(sub(to, from));
	const t_vec			nup = normalize(up);
	const t_vec			left = cross(forward, nup);
	const t_vec			true_up = cross(left, forward);
	const t_transform	orientation = {{
		left.x, left.y, left.z, 0,
		true_up.x, true_up.y, true_up.z, 0,
		-forward.x, -forward.y, -forward.z, 0,
		0, 0, 0, 1,
	}};
  // print_tupil("from", normalize(from));
  // printf ("dot %f\n", dot(point(0, 1, 0), vector(0, 1, 0)));
  // printf ("dot %f\n", dot(from, vector(0, 1, 0)));
  // if (is_equal_double(dot(normalize(from), vector(0, 1, 0)), 1)) {
  //    puts("hello"); 
  // }
	return (mat4_mult(orientation, translation(-from.x, -from.y, -from.z)));
}

inline t_point	apply(t_transform m, t_point p)
{
	if (matrix_is_equal(m, identity()))
		return (p);
	return ((t_point){{
			p.x * m.l1_c1 + p.y * m.l1_c2 + p.z * m.l1_c3 + p.w * m.l1_c4,
			p.x * m.l2_c1 + p.y * m.l2_c2 + p.z * m.l2_c3 + p.w * m.l2_c4,
			p.x * m.l3_c1 + p.y * m.l3_c2 + p.z * m.l3_c3 + p.w * m.l3_c4,
			p.x * m.l4_c1 + p.y * m.l4_c2 + p.z * m.l4_c3 + p.w * m.l4_c4,
		}});
}
