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

t_vec	vec_init(float x, float y, float z)
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

float	vec_distance(t_vec a, t_vec b, float sqrt_func(float))
{
	float	n1;
	float	n2;
	float	n3;
	float	distance;

	n1 = (a.x - b.x) * (a.x - b.x);
	n2 = (a.y - b.y) * (a.y - b.y);
	n3 = (a.z - b.z) * (a.z - b.z);
	distance = sqrt_func(n1 + n2 + n3);
	return (distance);
}

float	vec_dot_product(t_vec a, t_vec b)
{
	float	dot;

	dot = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (dot);
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

float	vec_lenght(t_vec a, float sqrt_func(float))
{
	float	lenght;

	lenght = sqrt_func(vec_dot_product(a, a));
	return (lenght);
}

t_vec	vec_scalar(t_vec a, float k)
{
	t_vec	x;

	x = (t_vec){{
		a.x * k,
		a.y * k,
		a.z * k,
	}};
	return (x);
}

t_vec	vec_normalize(t_vec v, float sqrt_func(float))
{
	t_vec	nv;
	float	len;
	float	invertLenght;

	len = vec_lenght(v, sqrt_func);
	if (len > 0)
	{
		invertLenght = 1 / sqrt_func(len);
		nv = (t_vec){{
			v.x * invertLenght,
			v.y * invertLenght,
			v.z * invertLenght,
		}};
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
	centroid = vec_scalar (centroid, (float)1 / 3);
	return (centroid);
}


// int main()
// {
	 // t_pos a = vec_init(4, 3, 0);
	 // t_pos b = vec_init(2, 1, 0);
	 // t_pos a = vec_init(1, 0, 0);
	 // t_pos b = vec_init(0, 1, 0);
//
	 // float distance = vec_distance(a, b, sqrtf);
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
