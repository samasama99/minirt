/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_position.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:03:55 by orahmoun          #+#    #+#             */
/*   Updated: 2022/09/03 14:08:40 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

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

t_optional_vector	parse_vector(const char *target)
{
	t_optional_array	array;
	t_optional_double	*p;

	array = split_string(target, ',');
	if (array.error || count_char(target, ',') != 2
		|| array_len(array.value) != 3)
		return ((t_optional_vector){.error = true});
	p = (t_optional_double[3]){
		parse_double(array.value[0]),
		parse_double(array.value[1]),
		parse_double(array.value[2]),
	};
	if (p[0].error || p[1].error || p[2].error)
		return ((t_optional_vector){.error = true});
	return ((t_optional_vector){
		.value = vector(p[0].value, p[1].value, p[2].value),
		.error = false,
	});
}
