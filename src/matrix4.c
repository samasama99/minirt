/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:14:01 by zsarir            #+#    #+#             */
/*   Updated: 2022/07/28 16:14:23 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"

bool	mat4_is_invertible(t_matrix4 m)
{
	return (mat4_determinant(m));
}

t_matrix4	inverse(t_matrix4 m)
{
	double	id;

	if (matrix_is_equal(m, identity()))
		return (identity());
	id = 1 / mat4_determinant(m);
	return ((t_matrix4){{
			.l1_c1 = mat4_cofactor(m, 0, 0) * id,
			.l1_c2 = mat4_cofactor(m, 1, 0) * id,
			.l1_c3 = mat4_cofactor(m, 2, 0) * id,
			.l1_c4 = mat4_cofactor(m, 3, 0) * id,
			.l2_c1 = mat4_cofactor(m, 0, 1) * id,
			.l2_c2 = mat4_cofactor(m, 1, 1) * id,
			.l2_c3 = mat4_cofactor(m, 2, 1) * id,
			.l2_c4 = mat4_cofactor(m, 3, 1) * id,
			.l3_c1 = mat4_cofactor(m, 0, 2) * id,
			.l3_c2 = mat4_cofactor(m, 1, 2) * id,
			.l3_c3 = mat4_cofactor(m, 2, 2) * id,
			.l3_c4 = mat4_cofactor(m, 3, 2) * id,
			.l4_c1 = mat4_cofactor(m, 0, 3) * id,
			.l4_c2 = mat4_cofactor(m, 1, 3) * id,
			.l4_c3 = mat4_cofactor(m, 2, 3) * id,
			.l4_c4 = mat4_cofactor(m, 3, 3) * id,}});
}
