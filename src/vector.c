/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:48:42 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/20 15:12:29 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

void	vec_print(char *vec_name, t_vec a)
{
	printf("vec %s\n|x = %.2f|\n|y = %.2f|\n|z = %.2f|\n",
				vec_name, a.x, a.y, a.z);
}

void	vec_print_2(char *vec_name, t_vec a)
{
	printf("vec %s\n|i = %10f|\n|j = %10f|\n|k = %10f|\n",
				vec_name, a.i, a.j, a.k);
}

void	vec_print_3(char *vec_name, t_vec a)
{
	printf("vec %s\n|i = %10f|\n|j = %10f|\n|k = %10f|\n",
				vec_name, a.v[0], a.v[1], a.v[2]);
}

t_vec	vec_init(double x, double y, double z)
{
	t_vec	vec;

	vec = (t_vec){{
		x,
		y,
		z,
	 }};
	return (vec);
}

t_vec	vec_sum(t_vec a, t_vec b)
{
	t_vec	x;

	x = (t_vec){{
		a.x + b.x,
		a.y + b.y,
		a.z + b.z,
	}};
	return (x);
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	t_vec	x;

	x = (t_vec){{
		a.x - b.x,
		a.y - b.y,
		a.z - b.z,
	}};
	return (x);
}

double	vec_distance(t_vec a, t_vec b, double sqrt_func(double))
{
	double	n1;
	double	n2;
	double	n3;
	double	distance;

	n1 = (a.x - b.x) * (a.x - b.x);
	n2 = (a.y - b.y) * (a.y - b.y);
	n3 = (a.z - b.z) * (a.z - b.z);
	distance = sqrt_func(n1 + n2 + n3);
	return (distance);
}

double	vec_dot_product(t_vec a, t_vec b)
{
	  return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_vec	vec_cross_product(t_vec a, t_vec b)
{
	t_vec	x;

	x = (t_vec){{
		(a.y * b.z) - (a.z * b.y),
		(a.z * b.x) - (a.x * b.z),
		(a.x * b.y) - (a.y * b.x),
	}};
	return (x);
}

double	vec_lenght(t_vec a, double sqrt_func(double))
{
	double	lenght;

	lenght = sqrt_func(vec_dot_product(a, a));
	return (lenght);
}

t_vec	vec_scalar(t_vec a, double k)
{
	t_vec	x;

	x = (t_vec){{
		a.x * k,
		a.y * k,
		a.z * k,
	}};
	return (x);
}

t_vec	vec_normalize(t_vec v, double sqrt_func(double))
{
	t_vec	nv;
	double	len;
	double	invertLenght;

	len = vec_lenght(v, sqrt_func);
	if (len > 0 && len != 1)
	{
		invertLenght = 1 / len;
		nv = (t_vec) {
			v.x * invertLenght,
			v.y * invertLenght,
			v.z * invertLenght,
		};
	}
	else
		nv = v;
	return (nv);
}

t_vec	vec_opose(t_vec v)
{
	t_vec	o;

	o = (t_vec){{
			v.x * -1,
			v.y * -1,
			v.z * -1,
	}};
	return (o);
}

t_vec	vec_mid(t_vec a, t_vec b)
{
	t_vec	o;

	o = vec_sum(a, b);
	o = vec_scalar(o, 0.5);
	return (o);
}

t_vec	vec_centroid(t_vec a, t_vec b, t_vec c)
{
	t_vec	centroid;

	centroid = (t_pos){{
			a.x + b.x + c.x,
			a.y + b.y + c.y,
			a.z + b.z + c.z,
	}};
	centroid = vec_scalar (centroid, (double)1 / 3);
	return (centroid);
}

bool  is_equal_float(float x, float y)
{
  const float EPSILON = 0.00001;
  if (fabsf(x - y) < EPSILON)
    return true;
  return false;
}

bool  is_equal_double(double x, double y)
{
  const double EPSILON = 0.00001;
  if (fabs(x - y) < EPSILON)
    return true;
  return false;
}

bool vec_is_equal(t_vec v1, t_vec v2)
{
  if (is_equal_double(v1.x, v2.x) == false) 
    return false;
  if (is_equal_double(v1.y, v2.y) == false) 
    return false;
  if (is_equal_double(v1.z, v2.z) == false) 
    return false;
  return true;
}


// int main()
// {
	 // t_pos a = vec_init(4, 3, 0);
	 // t_pos b = vec_init(2, 1, 0);
	 // t_pos a = vec_init(1, 0, 0);
	 // t_pos b = vec_init(0, 1, 0);
//
	 // double distance = vec_distance(a, b, sqrtf);
	 // vec_print("a", a);
	 // vec_print("b", b);
	 // printf ("distance :: %f\n", distance);
	 // vec_print("c", vec_scalar(vec_sum(a, b), 0.5));
	// t_vec a = vec_init(10, 20, -30);
	// t_vec b = vec_init(60, -50, 0);
	// t_vec c = vec_init(10, 20, 0);
	// t_vec d = vec_init(60, 30, 0);
	// vec_print("A", a);
	// vec_print("B", b);
	// vec_print("X", vec_sum(a, b));
	// vec_print("Y", vec_sub(a, b));
	// vec_print("Z", vec_cross_product(c, d));
	// vec_print("NZ", vec_cross_product(
				// vec_normalize(c, sqrtf)
				// , vec_normalize(d, sqrtf)));
	// vec_print("NNZ",
			// vec_normalize(
					// (vec_cross_product(
					// vec_normalize(c, sqrtf)
					// , vec_normalize(d, sqrtf)))
				// , sqrtf
				// ));
	// printf("A.B = %.2f\n", vec_dot_product(a, b));
	// printf("|A| = %.2f\n", vec_lenght(a, sqrtf));
	// vec_print("NA", vec_normalize(a, sqrtf));
// }
