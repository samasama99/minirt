#include "linear_algebra.h"
#include "main.h" 
#include <math.h>

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

double calc_du_sphere(t_image img, t_sphere sp, t_point p)
{
  t_fpair ij = ij_of_map(img.res, uv_of_sphere(sp, p));
  int i = ij.i;
  int j = ij.j;

  return ((linear_interpolation(i + 1, j, img) - linear_interpolation(i, j, img)) * 0.0000015);
  // return ((g_img.buffer[i + 1 + (j * g_img.res.width)] - g_img.buffer[i + (j * g_img.res.width)]) * 0.0000015);
}

double calc_dv_sphere(t_image img, t_sphere sp, t_point p)
{
  const t_fpair ij = ij_of_map(img.res, uv_of_sphere(sp, p));
  int i = ij.i;
  int j = ij.j;

//   return ((g_img.buffer[i + ((j + 1) * g_img.res.width)] - g_img.buffer[i + (j * g_img.res.width)])*0.0000015 );
  return ((linear_interpolation(i, j + 1, img) - linear_interpolation(i, j, img)) * 0.0000015);
}

t_vec	bm_normal_at_sphere(t_sphere sp, t_point p, t_image img)
{
	const t_vec		pu = pu_sphere(p);
	const t_vec		pv = pv_sphere(p, sp);
	const double	du = calc_du_sphere(img, sp, p);
	const double	dv = calc_dv_sphere(img, sp, p);
	
	if (dot(normalize(cross(pu, pv)), normalize(normal_at((t_shape)sp, p))) < 0
  		|| is_equal_double(dot(normalize(cross(pu, pv)), normalize(normal_at((t_shape)sp, p))), 0))
		return ((sub((cross(pu, pv)),
				(sum(scalar(pu, du), scalar(pv, dv))))));

	return ((sub((cross(pv, pu)),
				(sum(scalar(pu, du), scalar(pv, dv))))));
}

t_rgb	shade_hit_bm_sphere(t_comp comps, t_light l, t_sphere s, t_world w)
{
    const t_uv uv = uv_of_sphere(s, comps.over_point);
    const t_fpair ij = ij_of_map(s.img.res, uv);
    const int i = ij.i;
    const int j = ij.j;
  	const t_vec			lightv = normalize(sub(l.position, comps.over_point));
    t_color ucolor = (t_color)(int)s.img.buffer[i + (j * s.img.res.width)];

  	comps.shape.sphere.material.color = color((float)ucolor.red / 255.0, (float)ucolor.green / 255.0, (float)ucolor.blue / 255.0);
	const double		light_dot_normal = dot(lightv, normalize(bm_normal_at_sphere(comps.shape.sphere, comps.over_point, s.img)));

	return comps.shape.sphere.material.color;
}


t_rgb	shade_hit_bm_cylinder(t_comp comps, t_light l, t_cylinder s, t_world w)
{
    const t_uv uv = uv_of_cylinder(s, comps.over_point);
    const t_fpair ij = ij_of_map(s.img.res, uv);
    const int i = ij.i;
    const int j = ij.j;
  	const t_vec			lightv = normalize(sub(l.position, comps.over_point));
    t_color ucolor = (t_color)(int)s.img.buffer[i + (j * s.img.res.width)];

  	comps.shape.super.material.color = color((float)ucolor.red / 255.0, (float)ucolor.green / 255.0, (float)ucolor.blue / 255.0);
	return comps.shape.super.material.color;
}
t_rgb	shade_hit_bm_plane(t_comp comps, t_light l, t_plane s, t_world w)
{
    const t_uv uv = uv_of_plane(s, comps.over_point);
    const t_fpair ij = ij_of_map(s.img.res, uv);
    const int i = ij.i;
    const int j = ij.j;
  	const t_vec			lightv = normalize(sub(l.position, comps.over_point));
    t_color ucolor = (t_color)(int)s.img.buffer[i + (j * s.img.res.width)];

  	comps.shape.super.material.color = color((float)ucolor.red / 255.0, (float)ucolor.green / 255.0, (float)ucolor.blue / 255.0);
	return comps.shape.super.material.color;
}


