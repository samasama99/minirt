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

t_vec pu_sphere(t_point p)
{
  return vector(p.z * 2 * M_PI, 0, -p.x * 2 * M_PI);
}

t_vec pv_sphere(t_point p, t_sphere sp)
{
  const double phi = phi_sphere(sp,p);
  const double teta = teta_sphere(sp, p);

  return vector(p.y * cos(phi) * M_PI,
                -sp.radius * sin(teta) * M_PI,
                p.y * sin(phi) * M_PI);
}

// p.x + (p.y * img.res.x)

double calc_du_sphere(t_image img, t_sphere sp, t_point p)
{
  t_fpair ij = ij_of_map(img.res, uv_of_sphere(sp, p));
  int i = ij.i;
  int j = ij.j;

  return ((linear_interpolation(i + 1, j, img) - linear_interpolation(i, j, img)) * 0.0000015 );
//   return ((g_img.buffer[i + 1 + (j * g_img.res.width)] - g_img.buffer[i + (j * g_img.res.width)]) * 0.0000015);
}

double calc_dv_sphere(t_image img, t_sphere sp, t_point p)
{
  const t_fpair ij = ij_of_map(img.res, uv_of_sphere(sp, p));
  int i = ij.i;
  int j = ij.j;

//   return ((g_img.buffer[i + ((j + 1) * g_img.res.width)] - g_img.buffer[i + (j * g_img.res.width)])*0.0000015 );
  return ((linear_interpolation(i, j + 1, img) - linear_interpolation(i, j, img)) * 0.000001);
}

t_vec	bm_normal_at(t_sphere sp, t_point p, t_image img)
{
	const t_vec		pu = pu_sphere(p);
	const t_vec		pv = pv_sphere(p, sp);
	const double	du = calc_du_sphere(img, sp, p);
	const double	dv = calc_dv_sphere(img, sp, p);

	return ((sub((cross(pv, pu)),
				(sum(scalar(pu, du), scalar(pv, dv))))));
}
