/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:12:47 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/09 21:39:54 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"

double	mat3_determinant(t_matrix3 m)
{
	return ((m.l1_c1 * mat3_cofactor(m, 0, 0)
			+ m.l1_c2 * mat3_cofactor(m, 0, 1)
			+ m.l1_c3 * mat3_cofactor(m, 0, 2)));
}

double	mat4_minor(t_matrix4 m, int row, int col)
{
	t_matrix3	x;

	x = mat4_submatrix(m, row, col);
	return (mat3_determinant(x));
}

double	mat4_cofactor(t_matrix4 m, int row, int col)
{
	static t_matrix4	x;

	x = (t_matrix4){{
		1, -1, 1, -1,
		-1, 1, -1, 1,
		1, -1, 1, -1,
		-1, 1, -1, 1,}};
	return (x.m[row][col] * mat4_minor(m, row, col));
}

double	mat4_determinant(t_matrix4 m)
{
	return ((m.l1_c1 * mat4_cofactor(m, 0, 0)
			+ m.l1_c2 * mat4_cofactor(m, 0, 1)
			+ m.l1_c3 * mat4_cofactor(m, 0, 2)
			+ m.l1_c4 * mat4_cofactor(m, 0, 3)));
}
