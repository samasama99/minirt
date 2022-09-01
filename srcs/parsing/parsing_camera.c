#include "main.h"
#include "parsing.h"

t_optional_transform	get_camera_view(char *from, char *to)
{
	const t_optional_transform	error = {.error = true};
	t_optional_point			p_from;
	t_optional_point			p_to;
	t_vec						up;
	t_vec						direction;

	p_from = parse_position(from);
	p_to = parse_position(to);
	if (p_from.error || p_to.error)
		return (error);
	direction = sub(p_from.value, p_to.value);
	if (vec_is_equal(normalize(direction), vector(0, 1, 0))
		|| vec_is_equal(opose(normalize(direction)), vector(0, 1, 0)))
		up = vector(1, 0, 0);
	else
		up = vector(0, 1, 0);
	return ((t_optional_transform){
		.value = view_transform(p_from.value, p_to.value, up),
		.error = false,
	});
}

t_optional_camera	parse_camera(const t_optional_array elems, t_res res)
{
	const t_optional_camera	error = {.error = true};
	t_optional_transform	camera_view;
	t_camera				cam;
	t_optional_double		fov;
	static bool				already_parsed = false;

	if (elems.error || already_parsed)
		return (error);
	camera_view = get_camera_view(elems.value[1], elems.value[2]);
	fov = parse_fov(elems.value[3]);
	if (camera_view.error || fov.error)
		return (error);
	cam = camera(res.width, res.height, fov.value);
	cam.transform = camera_view.value;
	already_parsed = true;
	return ((t_optional_camera){
		.value = cam,
		.error = false,
	});
}


