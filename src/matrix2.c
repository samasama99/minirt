/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:11:53 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/10 09:45:17 by orahmoun         ###   ########.fr       */
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
	t_pair	ms;
	t_pair	ns;
	t_matrix2	n;

	ms = (t_pair){0, 0};
	ns = (t_pair){0, 0};
	while (ms.j < 3 && ns.j < 3)
	{
		if (ms.j == row)
			++ms.j;
		while (ms.i < 3 && ms.j < 3 && ns.i < 3 && ns.j < 3)
		{
			if (ms.i == col)
				++ms.i;
			n.m[ns.j][ns.i] = m.m[ms.j][ms.i];
			++ms.i;
			++ns.i;
		}
		ms.i = 0;
		ns.i = 0;
		++ms.j;
		++ns.j;
	}
	return (n);
}

t_matrix3	mat4_submatrix(t_matrix4 m, int row, int col)
{
	t_pair		ms;
	t_pair		ns;
	t_matrix3	n;

	ms = (t_pair){0, 0};
	ns = (t_pair){0, 0};
	while (ms.j < 4)
	{
		if (ms.j == row)
			++ms.j;
		while (ms.i < 4)
		{
			if (ms.i == col)
				++ms.i;
			n.m[ns.j][ns.i] = m.m[ms.j][ms.i];
			++ms.i;
			++ns.i;
		}
		ms.i = 0;
		ns.i = 0;
		++ms.j;
		++ns.j;
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
