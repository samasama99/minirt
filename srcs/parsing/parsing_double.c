/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:01:16 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/03 15:46:49 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

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
