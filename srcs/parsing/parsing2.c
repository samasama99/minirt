/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:30:56 by zsarir            #+#    #+#             */
/*   Updated: 2022/07/28 15:32:08 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_optional_double	parse_fractional(const char *target)
{
	const t_optional_int	fractional = parse_int(target);
	const t_optional_double	error = {.error = true};

	if (fractional.error)
		return (error);
	return ((t_optional_double){
		.value = ((double)fractional.value
			/ pow(10, int_len(fractional.value))),
		.error = false,
	});
}

t_optional_double	parse_double(const char *target)
{
	const t_optional_array	array = split_string(target, '.');
	const t_optional_double	error = {.error = true};
	t_optional_int			whole;
	t_optional_double		fractional;

	if (array.error || array.size > 2)
		return (error);
	whole = parse_int(array.value[0]);
	if (whole.error)
		return (error);
	if (array.size == 1)
	{
		return ((t_optional_double){
			.value = whole.value,
			.error = false,
		});
	}
	fractional = parse_fractional(array.value[1]);
	if (fractional.error)
		return (error);
	fractional.value = whole.sign * fractional.value;
	return ((t_optional_double){
		.value = whole.value + fractional.value,
		.error = false,
	});
}

t_optional_rgb	parse_rgb(const char *target)
{
	char				**splited;
	t_optional_double	*colors;

	if (target == NULL)
		return ((t_optional_rgb){.error = true});
	if (count_char(target, ',') != 2)
		return ((t_optional_rgb){.error = true});
	splited = ft_split(target, ',');
	if (array_len(splited) != 3)
		return ((t_optional_rgb){.error = true});
	colors = (t_optional_double[3]){
		parse_color_ratio(splited[0]),
		parse_color_ratio(splited[1]),
		parse_color_ratio(splited[2])};
	if (colors[0].error || colors[1].error || colors[2].error)
		return ((t_optional_rgb){.error = true});
	return ((t_optional_rgb){
		.value = color(colors[0].value, colors[1].value, colors[2].value),
		.error = false,
	});
}

t_optional_point	parse_position(const char *target)
{
	t_optional_array	array;
	t_optional_double	*p;

	array = split_string(target, ',');
	if (array.error || count_char(target, ',') != 2
		|| array_len(array.value) != 3)
		return ((t_optional_point){.error = true});
	p = (t_optional_double[3]){
		parse_double(array.value[0]),
		parse_double(array.value[1]),
		parse_double(array.value[2]),
	};
	if (p[0].error || p[1].error || p[2].error)
		return ((t_optional_point){.error = true});
	return ((t_optional_point){
		.value = point(p[0].value, p[1].value, p[2].value),
		.error = false,
	});
}

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
