/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:20:22 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/27 19:20:23 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"
#include "main.h" 
#include <math.h>

t_fpair ij_of_map(t_res res, t_uv uv)
{
  const double u = uv.u;
  const double v = uv.v;

	return ((t_fpair){{u * res.width, v * res.height}});
}

double linear_interpolation(double i, double j, t_image img)
{
    int k = i;
    int l = j;
    return  ((1 - (i - k)) * (1 - (j - l)) * get_color_at(img, k, l)
                      + (1 - (i - k)) * (j - l) * get_color_at(img, k, l + 1)
                      + (i - k) * (1 - (j - l)) * get_color_at(img, k + 1, l)
                      + (i - k) * (j - l) * get_color_at(img, k + 1, l + 1));
}

// t_vec	bm_normal_at(t_shape s, t_point p, t_image img)
// {
// 	if (s.type == Sphere)
// 	{
// 		return bm_normal_at_sphere(s.sphere, p, img);
// 	}
// 	puts("bm_normal_at unknown shape"), exit(1);
// 	return vector(0, 1, 0);
// }
