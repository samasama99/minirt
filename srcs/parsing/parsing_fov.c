#include <parsing.h>

t_optional_double	parse_fov(const char *target)
{
	t_optional_int	deg;

	deg = parse_int(target);
	if (deg.error)
		return ((t_optional_double){.error = true});
	if (deg.value < 0 || deg.value > 180)
		return ((t_optional_double){.error = true});
	return ((t_optional_double){
		.value = radians(deg.value),
		.error = false,
	});
}
