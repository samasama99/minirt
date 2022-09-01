#include "main.h"
#include "parsing.h"

typedef struct s_optional_cylinder_infos {
	t_optional_point			center;
	t_optional_point			normal;
	t_optional_double			diameter;
	t_optional_double			height;
	t_optional_rgb				color;
	t_cylinder					cy;
}		t_optional_cylinder_info;

t_optional_shape	parse_cylinder(const t_optional_array elems)
{
	const t_optional_shape		error = {.error = true};
	t_optional_cylinder_info	i;
	t_optional_image			image;
	t_optional_rgb						color2;

	if (elems.error)
		return (error);
	i.center = parse_position(elems.value[1]);
	i.normal = parse_position(elems.value[2]);
	i.diameter = parse_double(elems.value[3]);
	i.height = parse_double(elems.value[4]);
	i.color = parse_rgb(elems.value[5]);
  	image = parse_image_path(elems.value[5]);
	color2 = parse_rgb(elems.value[6]);
	if (i.center.error || i.diameter.error || (i.color.error && image.error))
		return (error);
	i.normal.value.w = 0;
	i.cy = make_cylinder(point(0, 0, 0), vector(0, 1, 0),
			(t_fpair){{i.diameter.value / 2.0, i.height.value}}, i.color.value);
	i.cy.t = 
 mat4_mult(translation(i.center.value.x, i.center.value.y,
				i.center.value.z),

		mat4_mult(mat4_mult(rotation_y(acos(dot(vector(0, 0, 1),
								normalize(i.normal.value)))),
				rotation_z(acos(dot(normalize(i.normal.value),
							vector(0, 1, 0))))),
							rotation_x(acos(dot(normalize(i.normal.value),
								vector(0, 1, 0))))));
	if (color2.error && image.error)
		i.cy.material.color = i.color.value;
	else if (image.error)
	{
		i.cy.checkerboard_color1 = i.color.value;
		i.cy.checkerboard_color2 = color2.value;
		i.cy.color_type = Checkerboard;
	} 
	else
    {
      i.cy.color_type = Texture;
      i.cy.img = image.value;
    }
	return ((t_optional_shape){.value = (t_shape)i.cy, .error = false});
}
