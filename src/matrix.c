/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:56:03 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/21 12:44:19 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "../libft/libft.h"
// old syntax
// void	f(a, b, x)
// int		a;
// int		b;
// float		x;
// {
	// a = 10;
	// b = 20;
	// x = 20;
// }
//
//
//
//
void	mat3_print(t_matrix3 mat)
{
	printf ("|%.2f %.2f %.2f|\n", mat.l1_c1, mat.l1_c2,  mat.l1_c3);
	printf ("|%.2f %.2f %.2f|\n", mat.l2_c1, mat.l2_c2,  mat.l2_c3);
	printf ("|%.2f %.2f %.2f|\n", mat.l3_c1, mat.l3_c2,  mat.l3_c3);
}

t_matrix3	mat3_mult(t_matrix3 mat1, t_matrix3 mat2)
{
	
	uint_fast8_t		i;
	uint_fast8_t		j;
	t_matrix3	mult;

	i = 0;
	j = 0;
	while(i < 3)
	{
        while (j < 3)
		  {
            mult.m[i][j] = mat1.m[i][0] * mat2.m[0][j] +
									mat1.m[i][1] * mat2.m[1][j] +
                         	mat1.m[i][2] * mat2.m[2][j];
				j++;
        }
		  j = 0;
		  i++;
    }
	return (mult);
}

t_matrix4	mat4_mult(t_matrix4 mat1, t_matrix4 mat2)
{
	uint_fast8_t		i;
	uint_fast8_t		j;
	t_matrix4	mult;

	i = 0;
	j = 0;
	while(i < 4)
	{
        while (j < 4)
		  {
            mult.m[i][j] = mat1.m[i][0] * mat2.m[0][j] +
									mat1.m[i][1] * mat2.m[1][j] +
                         	mat1.m[i][2] * mat2.m[2][j] +
                         	mat1.m[i][3] * mat2.m[3][j];
				j++;
        }
		  j = 0;
		  i++;
    }
	return (mult);
}

// multiply coeffs from row 1 with coeffs from column 1
// Ptransformed.x = P.x * c00 + P.y * c10 + P.z * c20
// multiply coeffs from row 1 with coeffs from column 2
// Ptransformed.y = P.x * c01 + P.y * c11 + P.z * c21
// multiply coeffs from row 1 with coeffs from column 3
// Ptransformed.z = P.x * c02 + P.y * c12 + P.z * c22

t_pos	vec3_multi_mat3(t_pos p, t_matrix3 mat)
{
	t_pos	new_point;

	new_point = vec_init(
				p.x * mat.l1_c1 + p.y * mat.l2_c1 + p.z * mat.l3_c1,
				p.x * mat.l1_c2 + p.y * mat.l2_c2 + p.z * mat.l3_c2,
				p.x * mat.l1_c3 + p.y * mat.l2_c3 + p.z * mat.l3_c3
				// p.x * mat.l1_c1 + p.y * mat.l1_c2 + p.z * mat.l1_c3,
				// p.x * mat.l2_c1 + p.y * mat.l2_c2 + p.z * mat.l2_c3,
				// p.x * mat.l3_c1 + p.y * mat.l3_c2 + p.z * mat.l3_c3
			);
	return (new_point);
}

t_pos	pos3_multi_mat4(t_pos p, t_matrix4 mat)
{
	float	w;
	t_pos	new_point;

	new_point = vec_init(
				p.x * mat.l1_c1 + p.y * mat.l2_c1 + p.z * mat.l3_c1 + mat.l4_c1,
				p.x * mat.l1_c2 + p.y * mat.l2_c2 + p.z * mat.l3_c2 + mat.l4_c2,
				p.x * mat.l1_c3 + p.y * mat.l2_c3 + p.z * mat.l3_c3 + mat.l4_c3 
			);
	w = p.x * mat.l1_c4 + p.y * mat.l2_c4 + p.z * mat.l3_c4 + mat.l4_c4;
	if (w != 1 && w != 0)
	{
		new_point.x /= w;
		new_point.y /= w;
		new_point.z /= w;
	}
	return (new_point);
}

t_matrix4	mat4_transpose(t_matrix4 m)
{
	uint8_t		i;
	uint8_t		j;
	t_matrix4	t;

	i = 0;
	j = 0;
	while(i < 4)
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

// int main()
// {
	// t_matrix3 matrix;
	// t_matrix3 matrix2;
	// t_matrix3 mult;
//
	// matrix = (t_matrix3){{
			// 1, 2, 3,
			// 4, 5, 6,
			// 7, 8, 9
	// }};
	// matrix2 = (t_matrix3){{
			// 1, 99, 3,
			// 4, 10, 6,
			// 5.20, 8.10, 9
	// }};
	// mult = mat3_mult(matrix ,matrix2);
//
	// mat3_print(matrix);
	// printf ("************\n");
	// mat3_print(matrix2);
	// printf ("************\n");
	// mat3_print(mult);
	// t_pos	pos = vec_init(1, 1, 1);
	// t_matrix3 identity = (t_matrix3){{
			// 1, 0, 0,
			// 0, 1, 0,
			// 0, 0, 1
	// }};
	// t_matrix3 scale = (t_matrix3){{
			// 2, 0, 0,
			// 0, 2, 0,
			// 0, 0, 2
	// }};
	// vec_print("p", pos);
	// mat3_print(identity);
	// vec_print("new_pos", pos3_multi_mat3(pos, identity));
	// vec_print("new_pos", pos3_multi_mat3(pos, scale));
// }
