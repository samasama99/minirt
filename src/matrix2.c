/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:11:53 by zsarir            #+#    #+#             */
/*   Updated: 2022/07/28 16:13:04 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"

t_matrix4	transpose(t_matrix4 m)
{
	size_t		i;
	size_t		j;
	t_matrix4	t;

	i = 0;
	j = 0;
	while (i < 4)
	{
		while (j < 4)
		{
			t.m[i][j] = m.m[j][i];
			j++;
		}
		j = 0;
		i++;
	}
	return (t);
}

t_matrix2	mat3_submatrix(t_matrix3 m, int row, int col)
{
	size_t		i;
	size_t		j;
	size_t		i2;
	size_t		j2;
	t_matrix2	n;

	i = 0;
	j = 0;
	i2 = 0;
	j2 = 0;
	while (j < 3 && j2 < 3)
	{
		if (j == row)
			++j;
		while (i < 3 && j < 3 && i2 < 3 && j2 < 3)
		{
			if (i == col)
				++i;
			n.m[j2][i2] = m.m[j][i];
			++i;
			++i2;
		}
		i = 0;
		i2 = 0;
		++j;
		++j2;
	}
	return (n);
}

t_matrix3	mat4_submatrix(t_matrix4 m, int row, int col)
{
	int			i;
	int			j;
	int			i2;
	int			j2;
	t_matrix3	n;

	i = 0;
	j = 0;
	i2 = 0;
	j2 = 0;
	while (j < 4)
	{
		if (j == row)
			++j;
		while (i < 4)
		{
			if (i == col)
				++i;
			n.m[j2][i2] = m.m[j][i];
			++i;
			++i2;
		}
		i = 0;
		i2 = 0;
		++j;
		++j2;
	}
	return (n);
}

double	mat3_minor(t_matrix3 m, int row, int col)
{
	t_matrix2	n;

	n = mat3_submatrix(m, row, col);
	return (mat2_determinant(n));
}

double	mat3_cofactor(t_matrix3 m, int row, int col)
{
	t_matrix3	s;

	s = (t_matrix3){{
		1, -1, 1,
		-1, 1, -1,
		1, -1, 1,}};
	return (s.m[row][col] * mat3_minor(m, row, col));
}
