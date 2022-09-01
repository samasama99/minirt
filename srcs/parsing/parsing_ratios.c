#include <parsing.h>

t_optional_double	parse_ratio(const char *target)
{
	const t_optional_array	array = split_string(target, '.');
	const t_optional_double	error = {.error = true};
	t_optional_int			whole;
	t_optional_int			fractional;

	if (array.error || array_len(array.value) > 2)
		return (error);
	whole = parse_digit(array.value[0]);
	if (whole.error)
		return (error);
	if (array.size == 1)
		return ((t_optional_double){
			.value = whole.value,
			.error = false,
		});
	fractional = parse_digit(array.value[1]);
	if (fractional.error)
		return (error);
	if (fractional.value / 10. + whole.value > 1.0
		|| fractional.value / 10. + whole.value < 0.0)
		return (error);
	return ((t_optional_double){
		.value = whole.value + fractional.value / 10.,
		.error = false,
	});
}

t_optional_double	parse_color_ratio(const char *target)
{
	int	num;

	if (target == NULL)
		return ((t_optional_double){.error = true});
	if (ft_isnumber(target) == false)
		return ((t_optional_double){.error = true});
	num = ft_atoi(target);
	if (num < 0 || num > 255)
		return ((t_optional_double){.error = true});
	return ((t_optional_double){
		.value = num / 255.0,
		.error = false,
	});
}
