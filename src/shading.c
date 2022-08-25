/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 16:44:23 by zsarir            #+#    #+#             */
/*   Updated: 2022/08/25 16:44:26 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"
#include "main.h"

t_rgb	ambient(t_material m, t_light l);

// t_rgb cb(t_uv uv)
// {
//   int i = uv.u * 1000;
//   int j = uv.v * 1000;
//   if ((i + j) % 2)
//     return black();
//   return color(1,1,1);
// }

int get_color_at(t_image img, int x, int y)
{
  return (img.buffer[x + (y * img.res.width)]);
}


t_rgb	shade_hit_bm(t_world w, t_comp comps, t_light l, t_intersection	inter)
{
    t_uv uv = uv_of_sphere(inter.shape.sphere, comps.over_point);


//   const t_vec pu = pu_sphere(comps.over_point);
//   const t_vec pv = pv_sphere(comps.over_point, comps.shape.sphere);

    // t_point p = sum(comps.over_point,  sum(normalize(cross(pv, pu)), vector(uv.u,  uv.v, 1)));
	t_point p = comps.over_point;
    t_fpair ij = ij_of_map(g_img.res, uv);
    int i = ij.i;
    int j = ij.j;
    // t_color ucolor = (t_color)(int)g_img.buffer[i + (j * g_img.res.width)];
    t_color ucolor = (t_color)(int)linear_interpolation(i, j, g_img);

  comps.shape.sphere.material.color = color((float)ucolor.red / 255.0, (float)ucolor.green / 255.0, (float)ucolor.blue / 255.0);
  comps.shape.sphere.material.ambient_color = black();
  comps.shape.sphere.material.specular = 0;
  comps.shape.sphere.material.shininess = 0;
  comps.shape.sphere.material.ambient_ratio = 0;
  comps.shape.sphere.material.diffuse = 0.9;
	double				reflect_dot_eye;
	const t_material	m = comps.shape.super.material;
	t_vec				reflectv;
	const t_vec			lightv = normalize(
			sub(l.position, comps.over_point));
			
	const double		light_dot_normal = dot(lightv, normalize(bm_normal_at(comps.shape.sphere, p, g_img)));
	// const double		light_dot_normal = dot(lightv, comps.normalv);

	// if (is_shadowed(w, comps.over_point, l) == true
	// 	|| light_dot_normal < 0)
	// 	return (black());
	reflectv = reflect(opose(lightv), comps.normalv);
	reflect_dot_eye = dot(reflectv, comps.eyev);
	return diffuse(m, l, light_dot_normal);
	return (lighting(
			m,
			l,
			light_dot_normal,
			reflect_dot_eye));
}


t_vec	reflect(t_vec in, t_vec norm)
{
	return (sub(in, scalar(norm, 2.0 * dot(in, norm))));
}

bool	is_shadowed(t_world w, t_point p, t_light l)
{
	const t_vec				v = sub(l.position, p);
	const double			d = magnitude(v);
	const t_vec				direction = normalize(v);
	const t_ray				r = ray(p, direction);
	const t_intersection	i = intersect_world(w, r).intersections[0];

	return ((i.t >= 0 && i.t < d) == true);
}

t_rgb	color_at(t_world w, t_ray r)
{
	const t_hit		h = intersect_world(w, r);
	t_rgb			c;
	t_comp			comp;
	t_intersection	inter;
	int				index;

	c = black();
	index = 0;
	if (h.count == 0)
		return (c);
	inter = hit(h);
	if (inter.t < 0)
		return (c);
	// while (index < w.amount_of_lights)
	// {
  comp = prepare_computations(inter, r);
  if (inter.shape.type == Sphere)
    c = shade_hit_bm(w, comp, w.lights[0], inter);
  else
		c = rgb_sum(shade_hit(w, comp, w.lights[index]), c);
		// ++index;
	// }
	// c = rgb_sub(c, rgb_scalar(
	// 			rgb_scalar(i.shape.super.material.ambient_color,
	// 				i.shape.super.material.ambient_ratio),
	// 			w.amount_of_lights - 1));
	return (c);
}

t_rgb	shade_hit(t_world w, t_comp comps, t_light l)
{
	double				reflect_dot_eye;
	const t_material	m = comps.shape.super.material;
	t_vec				reflectv;
	const t_vec			lightv = normalize(
			sub(l.position, comps.over_point));
	const double		light_dot_normal = dot(lightv, comps.normalv);

	// if (true)
	// 	return checker_pattern_at(comps.over_point);
	if (is_shadowed(w, comps.over_point, l) == true
		|| light_dot_normal < 0)
		return (ambient(m, l));
	reflectv = reflect(opose(lightv), comps.normalv);
	reflect_dot_eye = dot(reflectv, comps.eyev);
	return (lighting(
			m,
			l,
			light_dot_normal,
			reflect_dot_eye));
}

