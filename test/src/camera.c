#include "main.h"

static double	calc_half_width(const double aspect, const double half_view)
{
	if (aspect >= 1)
		return (half_view);
	return (half_view * aspect);
}

static double	calc_half_height(const double aspect, const double half_view)
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
		// .aspect = aspect,
		// .fov = fov,
		// .half_view = half_view,
		.half_width = half_width,
		.half_height = half_height,
		.pixel_size = (half_width * 2) / hsize,
		.transform = identity(),
	});
}

inline static t_point	calc_world_corr(t_camera c, int px, int py)
{
	const double	xoffset = (px + 0.5) * c.pixel_size;
	const double	yoffset = (py + 0.5) * c.pixel_size;

	return (point(c.half_width - xoffset, c.half_height - yoffset, -1));
}

t_ray	ray_for_pixel(t_camera c, int px, int py)
{
	const t_point		w = calc_world_corr(c, px, py);
	const t_transform	inv = inverse(c.transform);
	const t_point		pixel = apply(inv, point(w.x, w.y, w.z));
	const t_point		origin = apply(inv, point(0, 0, 0));
	const t_vec			direction = normalize(sub(pixel, origin));

	return (ray(origin, direction));
}
