/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:39:04 by orahmoun          #+#    #+#             */
/*   Updated: 2022/07/28 15:31:20 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <assert.h>

t_optional_int	parse_digit(const char *d)
{
	if (d == NULL || d[0] == '\0')
		return ((t_optional_int){.error = true});
	if (ft_strlen(d) != 1)
		return ((t_optional_int){.error = true});
	if (ft_isdigit(d[0]) != 1)
		return ((t_optional_int){.error = true});
	return ((t_optional_int){
		.value = ft_atoi(d),
		.error = false,
	});
}

t_optional_array	split_string(const char *line, const char delimiter)
{
	char	**array;

	if (line == NULL)
		return ((t_optional_array){.error = true});
	array = ft_split(line, delimiter);
	if (array == NULL)
		return ((t_optional_array){.error = true});
	return ((t_optional_array){
		.value = array,
		.size = array_len(array),
		.error = false,
	});
}

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

t_optional_int	parse_int(const char *target)
{
	int	sign;

	sign = 1;
	if (target == NULL)
		return ((t_optional_int){.error = true});
	if (ft_isnumber(target + (target[0] == '-')) == false)
		return ((t_optional_int){.error = true});
	if (target[0] == '-')
		sign = -1;
	return ((t_optional_int){
		.value = ft_atoi(target),
		.sign = sign,
		.error = false,
	});
}
