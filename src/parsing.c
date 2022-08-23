/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orahmoun <orahmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 20:41:23 by orahmoun          #+#    #+#             */
/*   Updated: 2022/08/23 12:38:52 by orahmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../libft/libft.h"
#include <stddef.h>
#include <stdio.h>

char	*read_file(int fd)
{
	char	*total;
	char	buffer[2];
	int		b;

	total = ft_strdup("\0");
	while (1)
	{
		b = read(fd, buffer, 1);
		if (b == -1)
		{
			perror("minirt :: Error");
			exit(1);
		}
		if (b == 0)
			break ;
		buffer[1] = '\0';
		total = ft_strjoin(total, buffer);
	}
	if (total && total[0] == '\0')
		return (NULL);
	return (total);
}

void	parse(t_data *data, int fd, t_res res)
{
	t_optional_array	lines;
	t_optional_array	array;
	t_optional_int		type;
	size_t				i;

	i = 0;
	lines = split_string(read_file(fd), '\n');
	if (lines.error || lines.size == 0)
		ft_exit(parse_string("minirt :: invalid file\n"), 2);
	while (i < lines.size)
	{
		array = split_string_space(lines.value[i++]);
		if (array.error || type.error)
			ft_exit(parse_string("parsing error"), 1);
		type = parse_type(array.value[0]);
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
