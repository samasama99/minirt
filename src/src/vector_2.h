/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 17:20:33 by orahmoun          #+#    #+#             */
/*   Updated: 2022/03/18 17:21:52 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VECTOR_H
# define VECTOR_H
# include "vector.h"

t_vec	vec_sum(t_vec a, t_vec b)
{
	t_vec	x;

	x = (t_vec){{
		a.x + b.x,
		a.z + b.z,
		a.z + b.z,
	}};
	return (x);
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	t_vec	x;

	x = (t_vec){{
		a.x - b.x,
		a.z - b.z,
		a.z - b.z,
	}};
	return (x);
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
#endif
