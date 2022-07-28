/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rt2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:18:52 by zsarir            #+#    #+#             */
/*   Updated: 2022/07/28 15:19:19 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parsing.h"

t_shape	unwrap_shape(t_optional_array array, t_line_type type)
{
	const t_optional_shape	m = parse_shape(array, type);

	if (m.error)
		ft_exit(parse_string("failed to parse a shape"), 1);
	return (m.value);
}

void	parse(t_data *data, int fd, t_res res)
{
	t_optional_string	line;
	t_optional_array	array;
	t_optional_int		type;

	line.is_null = false;
	while (line.is_null == false)
	{
		line = get_line(fd);
		if (line.is_null || is_equal_str(line.value, "\n"))
			continue ;
		printf("%s", line.value);
		line = parse_string(ft_strtrim(line.value, "\n"));
		array = split_string(line.value, ' ');
		type = parse_type(array.value[0]);
		if (line.is_null || array.error || type.error)
			ft_exit(parse_string("parsing error"), 1);
		if (type.value == e_camera)
			data->c = unwarp_camera(array, res);
		if (type.value == e_light)
			data->w = add_light(data->w, unwrap_light(array));
		if (type.value == e_ambient)
			data->ambient = unwrap_ambient(array);
		if (type.value == e_sphere || type.value == e_plane
			|| type.value == e_cylinder || type.value == e_cone)
			data->w = add_shape(data->w, unwrap_shape(array, type.value));
	}
}
