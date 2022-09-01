#include "main.h"
#include "parsing.h"

t_optional_light	parse_light(const t_optional_array elems)
{
	const t_optional_light	error = {.error = true};
	t_optional_point		pos;
	t_optional_double		brightness;
	t_optional_rgb			color;

	if (elems.error)
		return (error);
	pos = parse_position(elems.value[1]);
	brightness = parse_ratio(elems.value[2]);
	color = parse_rgb(elems.value[3]);
	if (pos.error || brightness.error || color.error)
		return (error);
	return ((t_optional_light){
		.value = point_light(pos.value,
			rgb_scalar(color.value, brightness.value)),
		.error = false,
	});
}


