#include "main.h"

t_plane	make_plane(t_point pos, t_norm norm)
{
	static int	id;

	return ((t_plane){
		.type = Plane,
		.id = ++id,
		.t = identity(),
		.material = material(),
		.position = pos,
		.normal = norm,
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

	if (fabs(r.direction.y) < EPSILON)
		return (no_intersection());
	t = -r.origin.y / r.direction.y;
	return ((t_hit){{intersection(t, pl)}, .count = 1});
}

t_vec	normal_at_plane(t_plane p)
{
	return (p.normal);
}
