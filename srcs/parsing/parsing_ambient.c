#include "main.h"
#include "parsing.h"

t_optional_material	parse_ambient(const t_optional_array elems)
{
	t_optional_double	ambient_ratio;
	t_optional_rgb		ambient_color;
	static bool			already_parsed = false;

	if (elems.error || already_parsed)
		return ((t_optional_material){.error = true});
	ambient_ratio = parse_ratio(elems.value[1]);
	ambient_color = parse_rgb(elems.value[2]);
	if (ambient_ratio.error || ambient_color.error)
		return ((t_optional_material){.error = true});
	already_parsed = true;
	return ((t_optional_material){
		.value = {
			.ambient_ratio = ambient_ratio.value,
			.ambient_color = ambient_color.value,
		},
		.error = false,
	});
}
