#include "main.h"

t_rgb	ambient(t_material m, t_light l);

t_vec	reflect(t_vec in, t_vec norm)
{
	return (sub(
		in,
		scalar(norm, 2.0 * dot(in, norm))
	));
}

bool	is_shadowed(t_world w, t_point p)
{
	const t_vec				v = sub(w.light.position, p);
	const double			d = magnitude(v);
	const t_vec				direction = normalize(v);
	const t_ray				r = ray(p, direction);
	const t_intersection	i = intersect_world(w, r).intersections[0];

	return ((i.t >= 0 && i.t < d) == true);
}

t_rgb color_at(t_world w, t_ray r) {
  const t_hit h = intersect_world(w, r);
  t_comp comp;
  t_intersection i;

  if (h.count == 0)
	return black();
  i = hit(h);
  if (i.t < 0)
	return black();
  comp = prepare_computations(i, r);
  return (shade_hit(w, comp));
}

t_rgb	shade_hit(t_world w, t_comp comps)
{
	const t_material	m = comps.shape.super.material;
	const t_vec			lightv = normalize(
			sub(w.light.position, comps.over_point));
	const double		light_dot_normal = dot(lightv, comps.normalv);
	t_vec				reflectv;
	double				reflect_dot_eye;

	if (is_shadowed(w, comps.over_point) == true
		|| light_dot_normal < 0)
		return (ambient(m, w.light));
	reflectv = reflect(opose(lightv), comps.normalv);
	reflect_dot_eye = dot(reflectv, comps.eyev);
	return (lighting(
			m,
			w.light,
			light_dot_normal,
			reflect_dot_eye));
}
