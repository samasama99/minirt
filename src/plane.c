#include "main.h"

t_plane	make_plane(t_point pos, t_norm norm)
{
	static int	id;

	return ((t_plane){
		.type = Plane,
		.id = ++id,
		.transform = identity(),
		.material = material(),
		.position = pos,
		.normal = normalize(norm),
	});
}

t_plane	plane(void)
{
	return (make_plane(point(0, 0, 0), vector(0, 1, 0)));
}

t_hit	intersect_plane(t_plane p, t_ray r)
{
	double			t;
	const t_shape	pl = {.plane = p};
	double			inter;
	double			d;

	inter = dot(p.normal, r.direction);
	if (fabs(inter) < EPSILON)
		return (no_intersection());
	d = dot(p.position, p.normal);
	t = (d - dot(p.normal, r.origin)) / inter;
	return ((t_hit){{intersection(t, pl)}, .count = 1});
}

t_vec	normal_at_plane(t_plane p)
{
	return (p.normal);
}
