/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:56:03 by orahmoun          #+#    #+#             */
/*   Updated: 2022/07/28 16:12:09 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"

double	mat2_determinant(t_matrix2 m)
{
	return (m.l1_c1 * m.l2_c2 - m.l1_c2 * m.l2_c1);
}

void	mat3_print(t_matrix3 mat)
{
	printf("|%.2f %.2f %.2f|\n", mat.l1_c1, mat.l1_c2, mat.l1_c3);
	printf("|%.2f %.2f %.2f|\n", mat.l2_c1, mat.l2_c2, mat.l2_c3);
	printf("|%.2f %.2f %.2f|\n", mat.l3_c1, mat.l3_c2, mat.l3_c3);
}

t_matrix3	mat3_mult(t_matrix3 mat1, t_matrix3 mat2)
{
	size_t		i;
	size_t		j;
	t_matrix3	mult;

	i = 0;
	j = 0;
	while (i < 3)
	{
		while (j < 3)
		{
			mult.m[i][j] = mat1.m[i][0] * mat2.m[0][j] + mat1.m[i][1]
				* mat2.m[1][j] + mat1.m[i][2] * mat2.m[2][j];
			j++;
		}
	j = 0;
	i++;
	}
	return (mult);
}

t_matrix4	mat4_mult(t_matrix4 mat1, t_matrix4 mat2)
{
	size_t		i;
	size_t		j;
	t_matrix4	mult;

	i = 0;
	j = 0;
	while (i < 4)
	{
		while (j < 4)
		{
			mult.m[i][j] = mat1.m[i][0] * mat2.m[0][j]
				+ mat1.m[i][1] * mat2.m[1][j]
				+ mat1.m[i][2] * mat2.m[2][j] + mat1.m[i][3] * mat2.m[3][j];
			j++;
		}
		j = 0;
		i++;
	}
	return (mult);
}

bool	matrix_is_equal(t_matrix4 m, t_matrix4 n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < 4)
	{
		while (i < 4)
		{
			if (is_equal_double(m.m[j][i], n.m[j][i]) == false)
				return (false);
			++i;
		}
		i = 0;
		++j;
	}
	return (true);
}
