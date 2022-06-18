#include "main.h"

bool	is_shadowed(t_world w, t_point p)
{
	const t_vec				v = sub(w.light.position, p);
	const double			d = magnitude(v);
	const t_vec				direction = normalize(v);
	const t_ray				r = ray(p, direction);
	const t_intersection	i = intersect_world(w, r).intersections[0];

	return ((i.t >= 0 && i.t < d) == true);
}

t_light	point_light(t_point position, t_rgb intensity)
{
	return ((t_light){
		.position = position,
		.intensity = intensity,
	});
}

t_rgb	ambient(t_material m, t_light l)
{
	const t_rgb	effective_color = rgb_product(m.color, l.intensity);

	return (rgb_scalar(effective_color, m.ambient));
}

t_rgb	diffuse(t_material m, t_light l, double light_dot_normal)
{
	const t_rgb	effective_color = rgb_product(m.color, l.intensity);

	return (rgb_scalar(effective_color, m.diffuse * light_dot_normal));
}

t_rgb	specular(t_material m, t_light l, double reflect_dot_eye)
{
	double	factor;

	if (reflect_dot_eye <= 0)
		return (black());
	factor = pow(reflect_dot_eye, m.shininess);
	return (rgb_scalar(l.intensity, m.specular * factor));
}

t_rgb	lighting(t_material m, t_light l, double light_norm, double reflect_eye)
{
	return (rgb_sums(
			ambient(m, l),
			diffuse(m, l, light_norm),
			specular(m, l, reflect_eye)));
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
