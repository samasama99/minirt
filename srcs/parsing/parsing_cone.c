#include "main.h"
#include "parsing.h"

typedef struct s_optional_cone_infos {
	t_optional_point		center;
	t_optional_point		normal;
	t_optional_double		diameter;
	t_optional_double		height;
	t_optional_rgb			color;
	t_cone					co;
}		t_optional_cone_info;



t_optional_shape	parse_cone(const t_optional_array elems)
{
	const t_optional_shape	error = {.error = true};
	t_optional_cone_info	i;

	if (elems.error)
		return (error);
	i.center = parse_position(elems.value[1]);
	i.normal = parse_position(elems.value[2]);
	i.diameter = parse_double(elems.value[3]);
	i.height = parse_double(elems.value[4]);
	i.color = parse_rgb(elems.value[5]);
	if (i.center.error || i.diameter.error || i.color.error)
		return (error);
	i.normal.value.w = 0;
	i.co = make_cone(point(0, 0, 0), vector(0, 1, 0),
			(t_fpair){{i.diameter.value / 2.0, i.height.value}}, i.color.value);
	i.co.t = 
 	mat4_mult(translation(i.center.value.x, i.center.value.y,
				i.center.value.z),

		mat4_mult(mat4_mult(rotation_y(acos(dot(vector(0, 0, 1),
								normalize(i.normal.value)))),
				rotation_z(acos(dot(normalize(i.normal.value),
							vector(0, 1, 0))))),
							rotation_x(acos(dot(normalize(i.normal.value),
								vector(0, 1, 0))))));
	i.co.color_type = Normal;
	return ((t_optional_shape){.value = (t_shape)i.co, .error = false});
}
