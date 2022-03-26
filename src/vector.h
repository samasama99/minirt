/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:48:42 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/20 15:03:03 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef VECTOR_H
# define VECTOR_H
# include <math.h>
# include <stdio.h>

typedef union u_vec3
{
	struct {
		float	x;
		float	y;
		float	z;
	};
	struct {
		float	i;
		float	j;
		float	k;
	};
	float		v[3];
}	t_vec;

typedef union u_matrix3
{
	struct {
		float		l1_c1;
		float		l1_c2;
		float		l1_c3;
		float		l2_c1;
		float		l2_c2;
		float		l2_c3;
		float		l3_c1;
		float		l3_c2;
		float		l3_c3;
	};
	float		n[9];
	float		m[3][3];
}	t_matrix3;

typedef union u_matrix4
{
	struct {
		float		l1_c1;
		float		l1_c2;
		float		l1_c3;
		float		l1_c4;
		float		l2_c1;
		float		l2_c2;
		float		l2_c3;
		float		l2_c4;
		float		l3_c1;
		float		l3_c2;
		float		l3_c3;
		float		l3_c4;
		float		l4_c1;
		float		l4_c2;
		float		l4_c3;
		float		l4_c4;
	};
	float		n[16];
	float		m[4][4];
}	t_matrix4;

typedef t_vec	t_pos;
typedef t_vec	t_norm;

// VEC OP //
// t_vec	vec_min(t_vec a, t_vec b);
// t_vec	vec_max(t_vec a, t_vec b);
// t_vec	vec_clamp(t_vec x, t_vec a, t_vec b);
t_vec	vec_sum(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_cross_product(t_vec a, t_vec b);
t_vec	vec_scalar(t_vec a, float k);
t_vec	vec_init(float x, float y, float z);
t_vec	vec_normalize(t_vec v, float sqrt_func(float));
t_vec	vec_opose(t_vec v);
t_vec	vec_mid(t_vec a, t_vec b);
t_vec	vec_centroid(t_vec a, t_vec b, t_vec c);

float	vec_distance(t_vec a, t_vec b, float sqrt_func(float));
float	vec_lenght(t_vec a, float sqrt(float));
float	vec_dot_product(t_vec a, t_vec b);

void	vec_print(char *vec_name, t_vec a);

// MAT OP //
void	mat3_print(t_matrix3 mat);
t_matrix3	mat3_mult(t_matrix3 mat1, t_matrix3 mat2);
t_matrix4	mat4_mult(t_matrix4 mat1, t_matrix4 mat2);
t_pos	pos3_multi_mat3(t_pos p, t_matrix3 mat);
t_vec	vec3_multi_mat3(t_pos p, t_matrix3 mat);

#endif
