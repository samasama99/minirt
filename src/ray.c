#include "main.h"

t_ray	ray(t_point origin, t_vec direction)
{
	return ((t_ray){
		.origin = origin,
		.direction = direction,
	});
}

t_point	ray_position(t_ray r, double t)
{
	return (sum(r.origin, scalar(r.direction, t)));
}

t_ray	ray_transform(t_ray ray, t_matrix4 m)
{
	return ((t_ray){
		.origin = apply(m, ray.origin),
		.direction = apply(m, ray.direction),
	});
}

t_vec	normal_at(t_shape shape, t_point world_point)
{
	t_vec				local_normal;
	t_vec				world_normal;
	const t_transform	shape_transform = shape.super.transform;
	const t_point		local_point = apply(inverse(shape_transform),
											world_point);

	if (shape.type == SuperShape)
		local_normal = vector(local_point.x, local_point.y, local_point.z);
	if (shape.type == Plane)
		local_normal = normal_at_plane(shape.plane);
	if (shape.type == Sphere)
		local_normal = normal_at_sphere(shape.sphere, local_point);
	world_normal = apply(transpose(inverse(shape_transform)),
			local_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}

t_material	material(void)
{
	return ((t_material){
		.color = color(1, 1, 1),
		.ambient_ratio = 0.1,
		.ambient_color = color(1, 1, 1),
		.diffuse = 0.9,
		.specular = 0.9,
		.shininess = 200.0,
	});
}

bool	is_inside_shape(t_vec normalv, t_vec eyev)
{
	return (dot(normalv, eyev) < 0);
}

t_comp	prepare_computations(t_intersection i, t_ray r)
{
	t_comp	comp;

	comp.t = i.t;
	comp.shape = i.shape;
	comp.point = ray_position(r, comp.t);
	comp.eyev = opose(r.direction);
	comp.normalv = normal_at(comp.shape, comp.point);
	if (is_inside_shape(comp.normalv, comp.eyev))
	{
		comp.inside = true;
		comp.normalv = opose(comp.normalv);
	}
	else
		comp.inside = false;
	comp.over_point = sum(comp.point, scalar(comp.normalv, EPSILON));
	return (comp);
}
