/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:48:42 by orahmoun          #+#    #+#             */
/*   Updated: 2022/07/24 18:19:58 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"

void	print_tupil(char *vec_name, t_vec a)
{
	printf("vec %s\n|x = %f|\n|y = %f|\n|z = %f|\n|w = %f|\n",
		vec_name, a.x, a.y, a.z, a.w);
}

t_vec	sum(t_vec a, t_vec b)
{
	return ((t_vec){{
			a.x + b.x,
			a.y + b.y,
			a.z + b.z,
			a.w + b.w,}});
}

t_vec	sub(t_vec a, t_vec b)
{
	return ((t_vec){{
			a.x - b.x,
			a.y - b.y,
			a.z - b.z,
			a.w - b.w,}});
}

inline double	dot(t_vec a, t_vec b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w));
}

inline t_vec	cross(t_vec a, t_vec b)
{
	return ((t_vec){{
			(a.y * b.z) - (a.z * b.y),
			(a.z * b.x) - (a.x * b.z),
			(a.x * b.y) - (a.y * b.x),
			0,}});
}

double	magnitude(t_vec a)
{
	return (sqrt(dot(a, a)));
}

t_vec	scalar(t_vec a, double k)
{
	return ((t_vec){{
			a.x * k,
			a.y * k,
			a.z * k,
			a.w * k,}});
}

t_vec	normalize(t_vec v)
{
	t_vec			nv;
	const double	len = magnitude(v);
	double			invertLenght;

	if (len > 0 && len != 1)
	{
		invertLenght = 1 / len;
		nv = (t_vec){{
			.x = v.x * invertLenght,
			.y = v.y * invertLenght,
			.z = v.z * invertLenght,
			.w = v.w * invertLenght,
		}};
	}
	else
		nv = v;
	return (nv);
}

t_vec	opose(t_vec v)
{
	return ((t_vec){{
			v.x * -1,
			v.y * -1,
			v.z * -1,
			v.w * -1,}});
}

bool 	is_equal_float(float x, float y)
{
	return (fabsf(x - y) < EPSILON);
}

bool  is_equal_double(double x, double y)
{
	return (fabs(x - y) < EPSILON);
}

bool	vec_is_equal(t_vec v1, t_vec v2)
{
	return (is_equal_double(v1.x, v2.x)
		&& is_equal_double(v1.y, v2.y)
		&& is_equal_double(v1.z, v2.z));
}

inline t_vec	vector(double x, double y, double z)
{
	return ((t_vec){{x, y, z, 0}});
}

inline t_point	point(double x, double y, double z)
{
	return ((t_point){{x, y, z, 1}});
}

inline t_pair	pair(double x, double y)
{
	return ((t_pair){{x, y}});
}
