#include "main.h"

double	calc_half_width(const double aspect, const double half_view)
{
	if (aspect >= 1)
		return (half_view);
	return (half_view * aspect);
}

double	calc_half_height(const double aspect, const double half_view)
{
	if (aspect >= 1)
		return (half_view / aspect);
	return (half_view);
}

t_camera	camera(const double hsize, const double vsize, const t_rad fov)
{
	const double	half_view = tan(fov / 2);
	const double	aspect = hsize / vsize;
	const double	half_width = calc_half_width(aspect, half_view);
	const double	half_height = calc_half_height(aspect, half_view);

	return ((t_camera){
		.hsize = hsize,
		.vsize = vsize,
		.aspect = aspect,
		.fov = fov,
		.half_view = half_view,
		.half_width = half_width,
		.half_height = half_height,
		.pixel_size = (half_width * 2) / hsize,
		.transform = identity(),
	});
}

t_pair	calc_world_corr(t_camera c, int px, int py)
{
	const double	xoffset = (px + 0.5) * c.pixel_size;
	const double	yoffset = (py + 0.5) * c.pixel_size;

	return (pair(c.half_width - xoffset, c.half_height - yoffset));
}

t_ray	ray_for_pixel(t_camera c, int px, int py)
{
	const t_pair		w = calc_world_corr(c, px, py);
	const t_transform	inv = inverse(c.transform);
	const t_point		pixel = apply_transformation(inv, point(w.x, w.y, -1));
	const t_point		origin = apply_transformation(inv, point(0, 0, 0));
	const t_vec			direction = normalize(sub(pixel, origin));

	return (ray(origin, direction));
}
