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
#define _USE_MATH_DEFINES
# include <math.h>
# include <stdio.h>
# include <stdbool.h>

typedef double t_deg;
typedef double t_rad;

typedef union u_pair_int
{
	struct { int width; int height; };
	struct { int x; int y; };
	struct { int i; int j; };
}	t_pair;

typedef t_pair t_res;

typedef union u_vec2
{
	struct {
		double	x;
		double	y;
	};
	struct {
		double	i;
		double	j;
	};
	double		v[2];
}	t_vec2;

typedef union u_vec3
{
	struct {
		double	x;
		double	y;
		double	z;
	};
	struct {
		double	i;
		double	j;
		double	k;
	};
	double		v[3];
}	t_vec3;

typedef union u_vec4
{
	struct {
		double	x;
		double	y;
		double	z;
		double	w;
	};
	struct {
		double	i;
		double	j;
		double	k;
		double	l;
	};
	double		v[4];
}	t_vec;

typedef union u_matrix2
{
	struct {
		double		l1_c1;
		double		l1_c2;
		double		l2_c1;
		double		l2_c2;
	};
	double		n[4];
	double		m[2][2];
}	t_matrix2;

typedef union u_matrix3
{
	struct {
		double		l1_c1;
		double		l1_c2;
		double		l1_c3;
		double		l2_c1;
		double		l2_c2;
		double		l2_c3;
		double		l3_c1;
		double		l3_c2;
		double		l3_c3;
	};
	double		n[9];
	double		m[3][3];
}	t_matrix3;

typedef union u_matrix4
{
	struct {
		double		l1_c1;
		double		l1_c2;
		double		l1_c3;
		double		l1_c4;
		double		l2_c1;
		double		l2_c2;
		double		l2_c3;
		double		l2_c4;
		double		l3_c1;
		double		l3_c2;
		double		l3_c3;
		double		l3_c4;
		double		l4_c1;
		double		l4_c2;
		double		l4_c3;
		double		l4_c4;
	};
	double		n[16];
	double		m[4][4];
}	t_matrix4;

typedef t_vec	t_point;
typedef t_vec	t_tupil;
typedef t_vec	t_norm;
typedef t_matrix4 t_transform;

// UTILS //
bool  is_equal_float(float x, float y);
bool  is_equal_double(double x, double y);
bool  vec_is_equal(t_vec v1, t_vec v2);
bool  matrix_is_equal(t_matrix4 m, t_matrix4 n);


// VEC OP //
// t_vec	vec_min(t_vec a, t_vec b);
// t_vec	vec_max(t_vec a, t_vec b);
// t_vec	vec_clamp(t_vec x, t_vec a, t_vec b);
t_vec	sum(t_vec a, t_vec b);
t_vec	sub(t_vec a, t_vec b);
t_vec	cross(t_vec a, t_vec b);
t_vec	scalar(t_vec a, double k);
t_vec	normalize(t_vec v);
t_vec	opose(t_vec v);
// t_vec	vec_mid(t_vec a, t_vec b);
// t_vec	vec_centroid(t_vec a, t_vec b, t_vec c);

double	distance(t_vec a, t_vec b);
double	magnitude(t_vec a);
double	dot(t_vec a, t_vec b);

t_vec vector(double x, double y, double z);
t_point point(double x, double y, double z);
t_pair pair(double x, double y);

void	print_tupil(char *vec_name, t_vec a);

// MAT OP //
void	mat3_print(t_matrix3 mat);
t_matrix3	mat3_mult(t_matrix3 mat1, t_matrix3 mat2);
t_matrix4	mat4_mult(t_matrix4 mat1, t_matrix4 mat2);
t_point	pos3_multi_mat3(t_point p, t_matrix3 mat);
t_vec	vec3_multi_mat3(t_point p, t_matrix3 mat);
t_point pos3_multi_mat4(t_point p, t_matrix4 mat);
t_point mat4_multi_pos3(t_matrix4 mat, t_point p);
t_matrix4 transpose(t_matrix4 m);
double mat2_determinant(t_matrix2 m);
t_matrix3 mat4_submatrix(t_matrix4 m, int row, int col);
t_matrix2 mat3_submatrix(t_matrix3 m, int row, int col);
double mat3_minor(t_matrix3 m, int row, int col);
double mat3_cofactor(t_matrix3 m, int row, int col);
double mat3_determinant(t_matrix3 m);
double mat4_cofactor(t_matrix4 m, int row, int col);
double mat4_determinant(t_matrix4 m);
bool mat4_is_invertible(t_matrix4 m);
t_matrix4 inverse(t_matrix4 m);

// TRANSFORM
t_matrix4 translation(double x, double y, double z);
t_matrix4 scaling(double x, double y, double z);
t_rad radians(t_deg deg);
t_matrix4 identity();
t_matrix4 rotation_x(t_rad deg);
t_matrix4 rotation_y(t_rad deg);
t_matrix4 rotation_z(t_rad deg);
t_matrix4 shearing(t_point x, t_point y, t_point z);
t_matrix4 transform(t_matrix4 r, t_matrix4 s, t_matrix4 t);
t_point apply_transformation(t_transform mat, t_point p);

#endif
