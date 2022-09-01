#include "main.h"
#include "parsing.h"

t_optional_shape	parse_plane(const t_optional_array elems)
{
	const t_optional_shape	error = {.error = true};
	t_optional_point		p;
	t_optional_point		normal;
	t_optional_rgb			color[2];
	t_optional_image			image;
	t_plane					pl;

	if (elems.error)
		return (error);
	p = parse_position(elems.value[1]);
	normal = parse_position(elems.value[2]);
	color[0] = parse_rgb(elems.value[3]);
  	image = parse_image_path(elems.value[3]);
	color[1] = parse_rgb(elems.value[4]);
	if (p.error || normal.error || (color[0].error && image.error))
		return (error);
	pl = plane();
	normal.value.w = 0;
	pl = make_plane(point(0, 0, 0), vector(0, 1, 0));
	pl.material = material();
	if (color[1].error && image.error)
		pl.material.color = color[0].value;
	else if (image.error)
	{
		puts("here");
		pl.checkerboard_color1 = color[0].value;
		pl.checkerboard_color2 = color[1].value;
		pl.color_type = Checkerboard;
	}
	else
	{
      pl.color_type = Texture;
      pl.img = image.value;
	}
	
	pl.transform = 
 mat4_mult(translation(p.value.x, p.value.y,
				p.value.z),
		mat4_mult(mat4_mult(rotation_y(acos(dot(vector(0, 0, 1),
								normalize(normal.value)))),
				rotation_z(acos(dot(normalize(normal.value),
							vector(0, 1, 0))))),
							rotation_x(acos(dot(normalize(normal.value),
								vector(0, 1, 0))))));
	return ((t_optional_shape){
		.value = (t_shape)pl,
		.error = false,
	});
}
