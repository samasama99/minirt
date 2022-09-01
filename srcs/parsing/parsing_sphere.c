#include "main.h"
#include "parsing.h"

t_optional_shape	parse_sphere(const t_optional_array elems)
{
	const t_optional_shape	error = {.error = true};
	t_optional_point		center;
	t_optional_double		diameter;
	t_optional_rgb			color[2];
	t_optional_image			image;
  	t_sphere sp;

	if (elems.error)
		return (error);
	center = parse_position(elems.value[1]);
	diameter = parse_double(elems.value[2]);
	color[0] = parse_rgb(elems.value[3]);
	color[1] = parse_rgb(elems.value[4]);
  	image = parse_image_path(elems.value[3]);

	if (center.error || diameter.error || (color[0].error && image.error))
		return (error);
    sp = make_sphere(center.value,
      diameter.value / 2.0,
      black());
    if (color[0].error == false) {
		if (color[1].error)
        	sp.material.color = color[0].value;
		else
		{
			sp.color_type = Checkerboard;
			sp.checkerboard_color1 = color[0].value;
			sp.checkerboard_color2 = color[1].value;
		}
    }
    else
    {
      sp.color_type = Texture;
      sp.img = image.value;
    }
  return ((t_optional_shape){
    .value = (t_shape)sp,
    .error = false,
  });
}
