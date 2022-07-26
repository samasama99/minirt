#include "main.h"

t_intersection	intersection(double t, t_shape shape)
{
	return ((t_intersection){.t = t, .shape = shape});
}

t_hit	no_intersection(void)
{
	return ((t_hit){{intersection(-1, (t_shape){Error})},
						.count = 0});
}

t_hit	intersect(const t_shape shape, const t_ray r)
{
	const t_ray	tr = ray_transform(r, inverse(shape.super.transform));

	if (shape.type == Sphere)
		return (intersect_sphere(shape.sphere, tr));
	if (shape.type == Plane)
		return (intersect_plane(shape.plane, tr));
	if (shape.type == Cylinder)
		return (intersect_cylinder(shape.cylinder, tr));
	if (shape.type == Cone)
		return (intersect_cone(shape.cone, tr));
	return (no_intersection());
}

t_intersection	hit(t_hit h)
{
	size_t			i;
	t_intersection	min_positive;

	i = 0;
	min_positive = h.intersections[0];
	while (i < h.count)
	{
		if (min_positive.t < 0 && h.intersections[i].t >= 0)
			min_positive = h.intersections[i];
		if (h.intersections[i].t >= 0 && h.intersections[i].t < min_positive.t)
			min_positive = h.intersections[i];
		++i;
	}
	if (min_positive.t < 0)
		return (intersection(-1, (t_shape){.type = Error}));
	return (min_positive);
}
