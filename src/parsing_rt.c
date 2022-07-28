/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsarir <zsarir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:38:52 by orahmoun          #+#    #+#             */
/*   Updated: 2022/07/28 15:21:55 by zsarir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "parsing.h"

void	ft_exit(t_optional_string err, int err_status)
{
	if (err.is_null == false)
		write(1, err.value, err.size);
	exit(err_status);
}

t_optional_string	get_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line == NULL || *line == '\0')
		return ((t_optional_string){.is_null = true});
	return ((t_optional_string){
		.value = line,
		.size = ft_strlen(line),
		.is_null = false,
	});
}

t_camera	unwarp_camera(t_optional_array array, t_res res)
{
	const t_optional_camera	c = parse_camera(array, res);

	if (c.error)
		ft_exit(parse_string("failed to parse the camera"), 1);
	return (c.value);
}

t_light	unwrap_light(t_optional_array array)
{
	const t_optional_light	l = parse_light(array);

	if (l.error)
		ft_exit(parse_string("failed to parse the light"), 1);
	return (l.value);
}

t_material	unwrap_ambient(t_optional_array array)
{
	const t_optional_material	m = parse_ambient(array);

	if (m.error)
		ft_exit(parse_string("failed to parse the ambient"), 1);
	return ((t_material){
		.ambient_color = m.value.ambient_color,
		.ambient_ratio = m.value.ambient_ratio,
	});
}
